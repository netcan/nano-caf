//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_ACTOR_SYSTEM_H
#define NANO_CAF_ACTOR_SYSTEM_H

#include <nano-caf/core/system_actor_context.h>
#include <nano-caf/core/actor_context.h>

NANO_CAF_NS_BEGIN

struct actor_system
   : private system_actor_context
   , actor_context {
   auto start(size_t num_of_workers) noexcept -> void;
   auto shutdown() noexcept -> void;
   auto power_off() noexcept -> void;

   using system_actor_context::get_num_of_actors;
   using system_actor_context::spawn;
   using system_actor_context::spawn_typed_actor;
   using system_actor_context::sched_jobs;

private:
   auto get_system_actor_context() -> system_actor_context& override { return *this; }
   auto self_handle() const noexcept -> intrusive_actor_ptr override { return nullptr; }
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_SYSTEM_H
