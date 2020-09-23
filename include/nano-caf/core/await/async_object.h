//
// Created by Darwin Yuan on 2020/7/27.
//

#ifndef NANO_CAF_ASYNC_OBJECT_H
#define NANO_CAF_ASYNC_OBJECT_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/thread_pool/resumable.h>
#include <nano-caf/core/msg/predefined-msgs.h>
#include <nano-caf/core/actor/intrusive_actor_ptr.h>
#include <nano-caf/core/await/promise.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <type_traits>
#include <functional>
#include <future>

NANO_CAF_NS_BEGIN

template <typename F, typename R, typename = std::enable_if_t<std::is_invocable_r_v<R, F>>>
struct async_object : resumable  {
   async_object(intrusive_actor_ptr sender, F&& f)
      : f_{std::move(f)}
      , sender_{sender}
      {}

   virtual auto resume() noexcept -> bool override {
      promise_.set_value(std::move(f_()), sender_);
      return true;
   }

   auto get_future(on_actor_context& context) {
      return promise_.get_future(context);
   }

private:
   F f_;
   promise<R> promise_;
   intrusive_actor_ptr sender_;
};


template <class F, class... Args>
class async_func {
   std::tuple<F, Args...> f_;

public:
   using result_type = std::invoke_result_t<F, Args...>;

   explicit async_func(F&& f, Args&&... args)
      : f_(std::move(f), std::move(args)...) {}

   async_func(async_func&& f) : f_(std::move(f.f_)) {}

   auto operator()() -> result_type {
      return execute(std::make_index_sequence<sizeof...(Args) + 1>{});
   }
private:
   template <size_t ... I>
   auto execute(std::index_sequence<I...>) -> result_type {
      return std::invoke(std::move(std::get<I>(f_))...);
   }
};

template <class T>
inline auto decay_copy(T&& t) -> std::decay_t<T> {
   return std::forward<T>(t);
}

template<typename F, typename ... Args, typename = std::enable_if_t<std::is_invocable_v<F, Args...>>>
auto make_async_object(const intrusive_actor_ptr& sender, F&& callable, Args&& ... args) {
   using func_obj = async_func<std::decay_t<F>, std::decay_t<Args>...> ;
   using result_type =  typename func_obj::result_type;
   auto obj = func_obj{decay_copy(std::forward<F>(callable)), decay_copy(std::forward<Args>(args))...};
   return new async_object<func_obj, result_type>{sender, std::move(obj)};
}

NANO_CAF_NS_END

#endif //NANO_CAF_ASYNC_OBJECT_H
