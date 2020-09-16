//
// Created by Darwin Yuan on 2020/8/27.
//

#ifndef NANO_CAF_ACTOR_REGISTRY_H
#define NANO_CAF_ACTOR_REGISTRY_H

#include <nano-caf/core/actor/make_actor.h>

NANO_CAF_NS_BEGIN

struct actor_registry {
   auto register_actor() -> void;
   auto deregister_actor() -> void;

   auto get_num_of_actors() const -> size_t;

private:
   std::atomic<size_t> num_of_actors_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_REGISTRY_H
