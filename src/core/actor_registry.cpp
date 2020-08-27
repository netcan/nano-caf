//
// Created by Darwin Yuan on 2020/8/27.
//

#include <nano-caf/core/actor_registry.h>

NANO_CAF_NS_BEGIN

auto actor_registry::register_actor() -> void {
   num_of_actors_.fetch_add(1, std::memory_order_relaxed);
}

auto actor_registry::deregister_actor() -> void {
   num_of_actors_.fetch_sub(1,std::memory_order_release);
}

auto actor_registry::get_num_of_actors() const -> size_t {
   return num_of_actors_.load(std::memory_order_relaxed);
}

NANO_CAF_NS_END