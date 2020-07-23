//
// Created by Darwin Yuan on 2020/7/23.
//

#ifndef NANO_CAF_SCHED_ACTOR_H
#define NANO_CAF_SCHED_ACTOR_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/resumable.h>
#include <nano-caf/core/actor_inbox.h>

NANO_CAF_NS_BEGIN

struct sched_actor
   : resumable
   , private actor_inbox {
   using actor_inbox::enqueue;
   auto resume() noexcept  -> resumable::result override;
};

NANO_CAF_NS_END

#endif //NANO_CAF_SCHED_ACTOR_H
