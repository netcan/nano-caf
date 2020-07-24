//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_MAKE_ACTOR_H
#define NANO_CAF_MAKE_ACTOR_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/actor_storage.h>
#include <nano-caf/core/actor/actor_control_block.h>

NANO_CAF_NS_BEGIN

template<typename T, typename ... Ts>
intrusive_actor_ptr
make_actor(actor_system& system, Ts&&...args) {
   auto storage = new actor_storage<T>(system, std::forward<Ts>(args)...);
   return intrusive_actor_ptr(&(storage->control), false);
}

NANO_CAF_NS_END

#endif //NANO_CAF_MAKE_ACTOR_H