//
// Created by Darwin Yuan on 2020/9/23.
//

#ifndef NANO_CAF_ON_ACTOR_CONTEXT_H
#define NANO_CAF_ON_ACTOR_CONTEXT_H

#include <nano-caf/core/actor/actor_timer_context.h>
#include <nano-caf/core/await/awaiter_repository.h>

NANO_CAF_NS_BEGIN

struct on_actor_context
   : actor_timer_context
   , awaiter_repository {};

NANO_CAF_NS_END

#endif //NANO_CAF_ON_ACTOR_CONTEXT_H
