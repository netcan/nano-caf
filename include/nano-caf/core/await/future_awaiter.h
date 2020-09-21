//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_FUTURE_AWAITER_H
#define NANO_CAF_FUTURE_AWAITER_H

#include <nano-caf/core/await/cancellable.h>
#include <memory>

NANO_CAF_NS_BEGIN

struct future_awaiter {
   future_awaiter() = default;
   explicit future_awaiter(std::shared_ptr<cancellable> object) : object_{object} {}

   auto valid() const noexcept -> bool {
      return static_cast<bool>(object_.lock());
   }

   auto cancel(status_t cause) noexcept -> void {
      auto object = object_.lock();
      if(object) {
         object->cancel(cause);
      }
   }

private:
   std::weak_ptr<cancellable> object_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_AWAITER_H
