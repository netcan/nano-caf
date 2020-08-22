//
// Created by Darwin Yuan on 2020/7/26.
//

#include <nano-caf/core/system_actor_context.h>
#include <iostream>

NANO_CAF_NS_BEGIN

auto system_actor_context::register_actor() -> void {
   num_of_actors_.fetch_add(1, std::memory_order_relaxed);
}

auto system_actor_context::deregister_actor() -> void {
   num_of_actors_.fetch_sub(1,std::memory_order_release);
}

auto system_actor_context::schedule_job(resumable& job) noexcept -> void {
   coordinator::schedule_job(job);
}

auto system_actor_context::wait_actors_done() -> void {
   while(get_num_of_actors() > 0) {
      std::this_thread::yield();
   }
}

auto system_actor_context::get_num_of_actors() const -> size_t {
   return num_of_actors_.load(std::memory_order_relaxed);
}

NANO_CAF_NS_END