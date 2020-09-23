//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_FUTURE_AWAITER_H
#define NANO_CAF_FUTURE_AWAITER_H

#include <nano-caf/core/await/cancellable.h>
#include <nano-caf/core/actor/actor_timer_context.h>
#include <memory>

NANO_CAF_NS_BEGIN

struct future_awaiter {
   future_awaiter() = default;
   explicit future_awaiter(actor_timer_context* context, std::shared_ptr<cancellable> object)
      : context_{context}, object_{object} {}

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
   inline auto time_guard(std::chrono::duration<Rep, Period> const& d) && noexcept -> future_awaiter& {
      if(context_ && valid()) {
         auto cb = std::make_shared<timeout_callback_t>([obj = object_](auto){
            auto cancellable = obj.lock();
            if(cancellable) {
               cancellable->cancel(status_t::timeout);
            }
         });
         context_->start_timer((uint64_t)std::chrono::microseconds(d).count(), false, cb);
      }

      return *this;
   }

private:
   actor_timer_context* context_;
   std::weak_ptr<cancellable> object_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_AWAITER_H
