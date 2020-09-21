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

struct cancellable_repository;

template<typename T>
struct future {
   using obj_type = std::shared_ptr<detail::future_object<T>>;
   future(obj_type obj, cancellable_repository& repository)
      : repository_{repository}
      , object_{std::move(obj)} {}

   auto valid() const noexcept -> bool {
      return static_cast<bool>(object_);
   }

   template<typename F_CALLBACK, typename F_FAIL>
   auto then(F_CALLBACK&& callback, F_FAIL&& on_fail) -> future_awaiter {
      auto awaiter = std::make_shared<single_future_awaiter<T, F_CALLBACK, F_FAIL>>(repository_, object_, std::forward<F_CALLBACK>(callback), std::forward<F_FAIL>(on_fail));
      if(!awaiter->destroyed()) {
         repository_.add_cancellable(awaiter);
         object_->add_notifier(awaiter);
      }
      return future_awaiter{std::move(awaiter)};
   }

private:
   cancellable_repository& repository_;
   obj_type object_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_H
