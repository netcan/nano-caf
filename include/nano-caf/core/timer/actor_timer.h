//
// Created by Darwin Yuan on 2020/8/22.
//

#ifndef NANO_CAF_ACTOR_TIMER_H
#define NANO_CAF_ACTOR_TIMER_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/result_t.h>
#include <nano-caf/core/msg/predefined-msgs.h>

NANO_CAF_NS_BEGIN

struct actor_timer {
   virtual auto start_timer(intrusive_actor_ptr self,
                    const duration& duration,
                    bool periodic = false) -> result_t<uint64_t> = 0;
   virtual auto stop_timer(const intrusive_actor_ptr& self, timer_id) -> void = 0;
   virtual auto clear_actor_timer(const intrusive_actor_ptr& self) -> void = 0;

   virtual ~actor_timer() = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_TIMER_H
