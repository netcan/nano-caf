//
// Created by Darwin Yuan on 2020/7/26.
//

#include <nano-caf/core/actor_context.h>

NANO_CAF_NS_BEGIN

auto actor_context::register_actor() -> void {
   num_of_actors_.fetch_add(std::memory_order_relaxed);
}

auto actor_context::unregister_actor() -> void {
   num_of_actors_.fetch_sub(std::memory_order_relaxed);
}

NANO_CAF_NS_END