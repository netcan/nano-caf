//
// Created by Darwin Yuan on 2020/7/26.
//

#include <nano-caf/core/system_actor_context.h>
#include <spdlog/spdlog.h>

NANO_CAF_NS_BEGIN

auto system_actor_context::schedule_job(resumable& job) noexcept -> void {
   coordinator::schedule_job(job);
}

auto system_actor_context::wait_actors_done() -> void {
   while(actor_registry::get_num_of_actors() > 0) {
      std::this_thread::yield();
   }
}

NANO_CAF_NS_END