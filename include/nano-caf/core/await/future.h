//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_FUTURE_H
#define NANO_CAF_FUTURE_H

#include <nano-caf/core/await/detail/future_object.h>
#include <nano-caf/core/await/detail/when_all_object.h>
#include <nano-caf/core/await/detail/future_callback_object.h>
#include <nano-caf/core/await/detail/future_proxy_object.h>
#include <nano-caf/core/await/future_concept.h>
#include <memory>

NANO_CAF_NS_BEGIN


//template<typename T>
//constexpr bool Is_Tuple = false;
//
//template<typename ... Ts>
//constexpr bool Is_Tuple<std::tuple<Ts...>> = true;

template<typename F, typename T>
struct invoke_tuple_result {
   constexpr static bool invokable = false;
};

template<typename F, typename ... Xs>
struct invoke_tuple_result<F, std::tuple<Xs...>> {
   using type = std::invoke_result_t<F, Xs...>;
   constexpr static bool invokable = true;
};

template<typename F, typename T>
using invoke_tuple_result_t = typename invoke_tuple_result<F, T>::type;

template<typename T>
struct promise;

template<typename T>
struct future;

template<typename>
struct future_trait;

template<typename T>
struct future_trait<future<T>> {
    using value_type = T;
};

template<typename FUTURE, typename = void>
struct future_then {
   using T = typename future_trait<FUTURE>::value_type;

   template<typename F, typename R = std::invoke_result_t<F, T>, typename = std::enable_if_t<!Is_Future<R>>>
   auto then(F&& callback) noexcept -> future<R> {
      if(get_future().context_ == nullptr || !get_future().object_) return {};

      auto cb = std::make_shared<detail::future_callback_object<R, F, T>>(*get_future().context_, get_future().object_, std::forward<F>(callback));
      return {*get_future().context_, cb};
   }

   template<typename F, typename R = std::invoke_result_t<F, T>, typename = std::enable_if_t<Is_Future<R>>>
   auto then(F&& callback) noexcept -> R {
      if(get_future().context_ == nullptr || !get_future().object_) return {};

      auto cb = std::make_shared<detail::future_proxy_object<R, F, T>>(*get_future().context_, get_future().object_, std::forward<F>(callback));
      return R{*get_future().context_, cb};
   }

   template<typename F, typename R = invoke_tuple_result_t<F, T>, typename = std::enable_if_t<!Is_Future<R>>>
   auto then(F&& f) noexcept -> future<invoke_tuple_result_t<F, T>> {
      if(get_future().context_ == nullptr || !get_future().object_) return {};

      auto nf = [=](auto && value) mutable -> R { return std::apply(f, value); };
      auto cb = std::make_shared<detail::future_callback_object<R, decltype(nf), T>>(*get_future().context_, get_future().object_, std::move(nf));

      return future<R>{*get_future().context_, cb};
   }

private:
   FUTURE& get_future() {
       return static_cast<FUTURE&>(*this);
   }
};

template<typename T>
struct future_then<future<T>, std::enable_if_t<std::is_same_v<T, void>>> {
   template<typename F, typename R = std::invoke_result_t<F>, typename = std::enable_if_t<!Is_Future<R>>>
   auto then(F&& callback) noexcept -> future<std::invoke_result_t<F>> {
      if(get_future().context_ == nullptr || !get_future().object_) return {};

      auto cb = std::make_shared<detail::future_callback_object<R, F, void>>(*get_future().context_, get_future().object_, std::forward<F>(callback));
      return {*get_future().context_, cb};
   }

   template<typename F, typename R = std::invoke_result_t<F>, typename = std::enable_if_t<Is_Future<R>>>
   auto then(F&& callback) noexcept -> std::invoke_result_t<F> {
      if(get_future().context_ == nullptr || !get_future().object_) return {};

      auto cb = std::make_shared<detail::future_proxy_object<R, F, void>>(*get_future().context_, get_future().object_, std::forward<F>(callback));
      return R{*get_future().context_, cb};
   }

private:
   using FUTURE = future<T>;
   FUTURE& get_future() {
       return static_cast<FUTURE&>(*this);
   }
};

template<typename T>
struct future final: future_then<future<T>> {
   using object_type = std::shared_ptr<detail::future_object<T>>;
   using value_type = T;

   future() noexcept = default;
   future(on_actor_context& context, object_type object) noexcept
      : context_{&context}, object_{std::move(object)}
   {}

   template<typename ... Ys, typename = std::enable_if_t<(sizeof...(Ys) > 1)>>
   future(on_actor_context& context, future<Ys>& ... futures) noexcept
      : context_{&context} {
      auto obj = std::make_shared<detail::when_all_object<Ys...>>(context, futures.object_ ...);
      if(obj != nullptr && obj->valid()) {
         obj->check_done();
         object_ = obj;
      }
   };

   template<typename F, typename = std::enable_if_t<std::is_invocable_r_v<void, F, status_t>>>
   auto fail(F&& on_fail) noexcept -> future<T>& {
      if(!object_) {
         on_fail(status_t::invalid_data);
      } else {
         object_->set_fail_handler(std::forward<F>(on_fail));
      }
      return *this;
   }

   auto cancel(status_t cause) noexcept -> void {
      if(object_) {
         object_->cancel(cause);
         object_.release();
      }
   }

   inline auto valid() const noexcept -> bool {
      return static_cast<bool>(object_);
   }

   ~future() noexcept {
      if(object_ && object_.unique() && !object_->ready()) {
         context_->add_future(object_);
      }
   }

private:
   template<typename R, typename F, typename A>
   friend struct detail::future_proxy_object;

   template<typename ... Xs>
   friend struct detail::when_all_object;

   template<typename>
   friend struct future;

   template<typename, typename>
   friend struct future_then;

private:
   on_actor_context* context_{};
   object_type object_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_H
