//
// Created by Darwin Yuan on 2020/7/26.
//

#ifndef NANO_CAF_ACTOR_CONTEXT_H
#define NANO_CAF_ACTOR_CONTEXT_H

#include <nano-caf/core/actor/make_actor.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <nano-caf/util/disable_copy.h>
#include <nano-caf/core/coordinator.h>
#include <nano-caf/core/actor/typed_actor_handle.h>

NANO_CAF_NS_BEGIN

struct system_actor_context;

struct actor_context {
   template<typename T, typename ... Ts>
   auto spawn(Ts&& ... args) noexcept -> actor_handle {
      return make_actor<T>(get_system_actor_context(), std::forward<Ts>(args)...);
   }

   template<typename A, typename T, typename ... Ts>
   auto spawn_typed_actor(Ts&& ... args) noexcept -> typed_actor_handle<A> {
      return make_actor<T>(get_system_actor_context(), std::forward<Ts>(args)...);
   }

   virtual ~actor_context() = default;

private:
   virtual auto get_system_actor_context() -> system_actor_context& = 0;
};

NANO_CAF_NS_END

#endif //NANO_CAF_SYSTEM_ACTOR_CONTEXT_H
