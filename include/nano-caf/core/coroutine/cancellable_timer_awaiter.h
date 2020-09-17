//
// Created by Darwin Yuan on 2020/9/17.
//

#ifndef NANO_CAF_CANCELLABLE_TIMER_AWAITER_H
#define NANO_CAF_CANCELLABLE_TIMER_AWAITER_H

#include <nano-caf/core/msg/predefined-msgs.h>
#include <nano-caf/core/timer/timer_id_t.h>

NANO_CAF_NS_BEGIN

struct cancellable_timer_awaiter {
   virtual auto cancel() noexcept -> void = 0;
   virtual auto matches(timer_id_t id) const noexcept -> bool = 0;
   virtual ~cancellable_timer_awaiter() = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_CANCELLABLE_TIMER_AWAITER_H
