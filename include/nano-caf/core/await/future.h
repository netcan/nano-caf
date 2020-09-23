//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_FUTURE_H
#define NANO_CAF_FUTURE_H

#include <nano-caf/core/await/future_object.h>
#include <nano-caf/core/await/single_future_awaiter.h>
#include <nano-caf/core/await/future_awaiter.h>
#include <memory>

NANO_CAF_NS_BEGIN

struct on_actor_context;

template<typename ... Xs>
struct multi_future;

template<typename T>
struct future {
   using obj_type = std::shared_ptr<detail::future_object<T>>;
   future() noexcept = default;
   future(obj_type obj, on_actor_context& context) noexcept
      : context_{&context}
      , object_{std::move(obj)} {}

   auto valid() const noexcept -> bool {
      return static_cast<bool>(object_);
   }

   auto ready() const noexcept -> bool {
      return valid() && object_->ready();
   }

   template<typename F_CALLBACK, typename F_FAIL>
   auto then(F_CALLBACK&& callback, F_FAIL&& on_fail) noexcept -> future_awaiter {
      if(context_ == nullptr || !object_) {
         on_fail(status_t::invalid_data);
         return {};
      }

      auto awaiter = std::make_shared<single_future_awaiter<T, F_CALLBACK, F_FAIL>>(*context_, object_, std::forward<F_CALLBACK>(callback), std::forward<F_FAIL>(on_fail));
      if(!awaiter->destroyed()) {
         context_->add_awaiter(awaiter);
         object_->add_notifier(awaiter);
      }
      return future_awaiter{std::move(awaiter)};
   }

   template<typename F_CALLBACK>
   auto on_succeed(F_CALLBACK&& callback) noexcept -> future_awaiter {
      return then(std::forward<F_CALLBACK>(callback), [](auto){});
   }

private:
   template<typename ... Xs>
   friend struct multi_future;

private:
   on_actor_context* context_{};
   obj_type object_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_H
