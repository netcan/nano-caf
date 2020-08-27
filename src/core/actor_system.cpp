//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/actor_system.h>
#include <iostream>

NANO_CAF_NS_BEGIN

auto actor_system::start(size_t num_of_workers) noexcept -> void {
   coordinator::launch(num_of_workers);
   actor_timer::start();
}

auto actor_system::shutdown() noexcept -> void{
   wait_actors_done();
   coordinator::shutdown();
   actor_timer::stop();
}

auto actor_system::power_off() noexcept -> void {
   actor_timer::stop();
   coordinator::shutdown();
}

NANO_CAF_NS_END