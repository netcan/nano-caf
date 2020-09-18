//
// Created by Darwin Yuan on 2020/8/17.
//

#ifndef NANO_CAF_SYSTEM_ACTOR_CONTEXT_H
#define NANO_CAF_SYSTEM_ACTOR_CONTEXT_H

#include <nano-caf/core/actor/make_actor.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <nano-caf/util/disable_copy.h>
#include <nano-caf/core/thread_pool/coordinator.h>
#include <nano-caf/core/actor/typed_actor_handle.h>
#include <nano-caf/core/timer/actor_timer.h>
#include <nano-caf/core/actor_registry.h>

NANO_CAF_NS_BEGIN

struct system_actor_context
   : protected coordinator
   , public actor_registry
   , protected actor_timer
   , private disable_copy {

   explicit system_actor_context(std::size_t num_of_workers) noexcept
      : coordinator{num_of_workers} {}

   template<typename T, typename ... Ts>
   auto spawn(Ts&& ... args) noexcept -> actor_handle {
      return make_actor<T>(*this, std::forward<Ts>(args)...);
   }

   template<typename A, typename T, typename ... Ts>
   auto spawn_typed_actor(Ts&& ... args) noexcept -> typed_actor_handle<A> {
      return make_actor<T>(*this, std::forward<Ts>(args)...);
   }

   auto schedule_job(resumable& job) noexcept -> void;

   using coordinator::sched_jobs;
   using actor_timer::start_timer;
   using actor_timer::stop_timer;
   using actor_timer::clear_actor_timer;

protected:
   auto wait_actors_done() -> void;
};

NANO_CAF_NS_END

#endif //NANO_CAF_SYSTEM_ACTOR_CONTEXT_H
