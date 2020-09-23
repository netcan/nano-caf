//
// Created by Darwin Yuan on 2020/9/22.
//

#ifndef NANO_CAF_MULTI_FUTURE_H
#define NANO_CAF_MULTI_FUTURE_H

#include <nano-caf/core/await/future.h>
#include <nano-caf/core/await/multi_future_awaiter.h>
#include <memory>

NANO_CAF_NS_BEGIN

struct cancellable_repository;

template<typename ... Xs>
struct multi_future {
   multi_future() noexcept = default;
   multi_future(on_actor_context& context, future<Xs>& ... objects) noexcept
      : context_{&context}
      , objects_{objects.object_ ...} {
      init(std::index_sequence_for<Xs...>{});
   }

   multi_future(multi_future const&&) = delete;
   auto operator=(multi_future const&&) -> multi_future& = delete;

   auto valid() const noexcept -> bool {
      return valid_;
   }

   template<typename F_CALLBACK, typename F_FAIL,
      typename = std::enable_if_t<std::is_invocable_r_v<void, F_CALLBACK, const Xs& ...> &&
      std::is_invocable_r_v<void, F_FAIL, status_t>>>
   auto then(F_CALLBACK&& callback, F_FAIL&& on_fail) noexcept -> future_awaiter {
      if(context_ == nullptr || !valid_) {
         on_fail(status_t::invalid_data);
         return {};
      }

      auto awaiter = std::make_shared<multi_future_awaiter<F_CALLBACK, F_FAIL, Xs...>>(*context_, std::forward<F_CALLBACK>(callback), std::forward<F_FAIL>(on_fail), std::move(objects_));
      if(!awaiter->destroyed()) {
         context_->add_cancellable(awaiter);
         awaiter->register_notifier();
      }
      return future_awaiter{context_, awaiter};
   }

   template<typename F_CALLBACK,
      typename = std::enable_if_t<std::is_invocable_r_v<void, F_CALLBACK, const Xs& ...>>>
   auto on_succeed(F_CALLBACK&& callback) && noexcept -> future_awaiter {
      return this->then(std::forward<F_CALLBACK>(callback), [](auto){});
   }

private:
   template<std::size_t ... I>
   auto init(std::index_sequence<I...>) {
      valid_ = (std::get<I>(objects_) && ...);
   }

private:
   on_actor_context* context_{};
   std::tuple<std::shared_ptr<detail::future_object<Xs>>...> objects_;
   bool valid_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_MULTI_FUTURE_H
