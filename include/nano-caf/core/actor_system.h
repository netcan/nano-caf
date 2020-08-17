//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_ACTOR_SYSTEM_H
#define NANO_CAF_ACTOR_SYSTEM_H

#include <nano-caf/core/system_actor_context.h>

NANO_CAF_NS_BEGIN

struct actor_system
   : system_actor_context {
   auto start(size_t num_of_workers) noexcept -> void;
   auto shutdown() noexcept -> void;
   auto power_off() noexcept -> void;

   using system_actor_context::get_num_of_actors;
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_SYSTEM_H
