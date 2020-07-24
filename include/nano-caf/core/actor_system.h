//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_ACTOR_SYSTEM_H
#define NANO_CAF_ACTOR_SYSTEM_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/disable_copy.h>
#include <nano-caf/core/coordinator.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <nano-caf/core/actor/make_actor.h>

NANO_CAF_NS_BEGIN

struct actor_system: private coordinator, disable_copy {
   auto start(size_t num_of_workers) noexcept -> void;
   auto stop() noexcept -> void;

   auto schedule_job(resumable& job) noexcept -> void;

   template<typename T, typename ... Ts>
   auto spawn(Ts&& ... args) noexcept -> actor_handle {
      return make_actor<T>(*this, std::forward<Ts>(args)...);
   }

};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_SYSTEM_H
