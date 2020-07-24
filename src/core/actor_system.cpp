//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/actor_system.h>

NANO_CAF_NS_BEGIN

auto actor_system::start(size_t num_of_workers) noexcept -> void {
   coordinator::launch(num_of_workers);
}

auto actor_system::stop() noexcept -> void{
   coordinator::stop();
}

auto actor_system::schedule_job(resumable& job) noexcept -> void {
   coordinator::schedule_job(job);
}

NANO_CAF_NS_END