//
// Created by Darwin Yuan on 2020/7/26.
//

#ifndef NANO_CAF_ACTOR_CONTEXT_H
#define NANO_CAF_ACTOR_CONTEXT_H

#include <nano-caf/core/actor/make_actor.h>
#include <nano-caf/core/actor/actor_handle.h>

NANO_CAF_NS_BEGIN

struct actor_context  {
   template<typename T, typename ... Ts>
   auto spawn(Ts&& ... args) noexcept -> actor_handle {
      return make_actor<T>(*this, std::forward<Ts>(args)...);
   }

   virtual auto schedule_job(resumable& job) noexcept -> void = 0;

   auto register_actor() -> void;
   auto unregister_actor() -> void;

private:
   std::atomic<size_t> num_of_actors_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_CONTEXT_H
