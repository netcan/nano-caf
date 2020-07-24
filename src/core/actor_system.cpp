//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/actor_system.h>

NANO_CAF_NS_BEGIN

auto actor_system::start(size_t num_of_workers) {
   coordinator::launch(num_of_workers);
}

auto actor_system::stop() {
   coordinator::stop();
}

NANO_CAF_NS_END