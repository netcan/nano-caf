//
// Created by Darwin Yuan on 2020/7/23.
//

#include <nano-caf/core/sched_actor.h>

NANO_CAF_NS_BEGIN

auto sched_actor::resume() noexcept  -> resumable::result {
   return resumable::result::awaiting_message;
}

NANO_CAF_NS_END