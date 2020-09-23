//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_FUTURE_AWAITER_H
#define NANO_CAF_FUTURE_AWAITER_H

#include <nano-caf/core/await/awaiter.h>
#include <nano-caf/core/actor/actor_timer_context.h>
#include <memory>

NANO_CAF_NS_BEGIN

struct future_awaiter {
   future_awaiter() = default;
   explicit future_awaiter(std::shared_ptr<awaiter> object)
      : object_{object} {}

   auto valid() const noexcept -> bool {
      return static_cast<bool>(object_.lock());
   }

   auto cancel(status_t cause) noexcept -> void {
      auto object = object_.lock();
      if(object) {
         object->cancel(cause);
      }
   }

   template<typename Rep, typename Period>
   auto time_guard(std::chrono::duration<Rep, Period> const& d) && noexcept -> future_awaiter& {
      auto object = object_.lock();
      if(object) {
         object->await((uint64_t) std::chrono::microseconds(d).count(), object_);
      }
      return *this;
   }

private:
   std::weak_ptr<awaiter> object_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_AWAITER_H
