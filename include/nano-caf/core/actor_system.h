//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_ACTOR_SYSTEM_H
#define NANO_CAF_ACTOR_SYSTEM_H

#include <nano-caf/core/actor_context.h>

NANO_CAF_NS_BEGIN

struct actor_system
   : private actor_context {
   auto start(size_t num_of_workers) noexcept -> void;
   auto stop() noexcept -> void;

   using actor_context::spawn;
   using actor_context::get_num_of_actors;
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_SYSTEM_H
