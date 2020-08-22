//
// Created by Darwin Yuan on 2020/8/17.
//

#ifndef NANO_CAF_SYSTEM_ACTOR_CONTEXT_H
#define NANO_CAF_SYSTEM_ACTOR_CONTEXT_H

#include <nano-caf/core/actor/make_actor.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <nano-caf/util/disable_copy.h>
#include <nano-caf/core/coordinator.h>
#include <nano-caf/core/actor/typed_actor_handle.h>
#include <nano-caf/core/timer/timer_scheduler.h>

NANO_CAF_NS_BEGIN

struct system_actor_context
   : protected coordinator
   , protected timer_scheduler
   , private disable_copy {

   template<typename T, typename ... Ts>
   auto spawn(Ts&& ... args) noexcept -> actor_handle {
      return make_actor<T>(*this, std::forward<Ts>(args)...);
   }

   template<typename A, typename T, typename ... Ts>
   auto spawn_typed_actor(Ts&& ... args) noexcept -> typed_actor_handle<A> {
      return make_actor<T>(*this, std::forward<Ts>(args)...);
   }

   auto schedule_job(resumable& job) noexcept -> void;

   auto register_actor() -> void;
   auto deregister_actor() -> void;

   using coordinator::sched_jobs;
   using timer_scheduler::start_timer;
   using timer_scheduler::stop_timer;
   using timer_scheduler::clear_actor_timer;

protected:
   auto wait_actors_done() -> void;

   auto get_num_of_actors() const -> size_t;

private:
   std::atomic<size_t> num_of_actors_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_SYSTEM_ACTOR_CONTEXT_H
