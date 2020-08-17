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
#include <nano-caf/core/actor_context.h>

NANO_CAF_NS_BEGIN

struct system_actor_context
   : protected coordinator
   , private disable_copy
   , public actor_context {

   auto schedule_job(resumable& job) noexcept -> void;

   auto register_actor() -> void;
   auto deregister_actor() -> void;

   using coordinator::sched_jobs;

protected:
   auto wait_actors_done() -> void;

   auto get_num_of_actors() const -> size_t;

private:
   auto get_system_actor_context() -> system_actor_context& override { return *this; }

private:
   std::atomic<size_t> num_of_actors_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_SYSTEM_ACTOR_CONTEXT_H