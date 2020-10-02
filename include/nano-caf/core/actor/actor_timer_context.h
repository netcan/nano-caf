//
// Created by Darwin Yuan on 2020/9/23.
//

#ifndef NANO_CAF_ACTOR_TIMER_CONTEXT_H
#define NANO_CAF_ACTOR_TIMER_CONTEXT_H

#include <nano-caf/core/msg/predefined-msgs.h>
#include <nano-caf/util/result_t.h>

NANO_CAF_NS_BEGIN

struct actor_timer_context {
   virtual auto start_timer(timer_spec const& spec, bool periodic, timeout_callback_t&& callback) -> result_t<timer_id_t> = 0;
   virtual auto stop_timer(timer_id_t timer_id) -> void = 0;
   virtual ~actor_timer_context() = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_TIMER_CONTEXT_H
