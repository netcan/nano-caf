//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_ACTOR_STORAGE_H
#define NANO_CAF_ACTOR_STORAGE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/message_element.h>
#include <nano-caf/core/actor/lifo_inbox.h>
#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/actor/sched_actor.h>

NANO_CAF_NS_BEGIN

template<typename T>
struct actor_storage  {
   template<typename ... Ts>
   actor_storage(actor_system& system, Ts&& ... args)
   : control{system, data_dtor, block_dtor} {
      new (&value) internal_actor(std::forward<Ts>(args)...);
   }

private:
   static auto data_dtor(sched_actor* ptr) -> void {
      static_cast<internal_actor*>(ptr)->~internal_actor();
   }

   static auto block_dtor(actor_control_block* ptr) noexcept -> void {
      operator delete(reinterpret_cast<actor_storage*>(ptr));
   }

public:
   static_assert(sizeof(actor_control_block) <= CACHE_LINE_SIZE);
   actor_control_block control;

private:
   char padding[CACHE_LINE_SIZE - sizeof(control)];

   struct internal_actor : sched_actor, private T {
      template<typename ... Args>
      internal_actor(Args&&...args) : T(std::forward<Args>(args)...) {}

      auto exit(exit_reason reason) -> void override {
         sched_actor::exit_(reason);
      }

      auto self() -> actor_control_block& override {
         return *sched_actor::to_ctl();
      }

      auto user_defined_handle_msg(const message_element& msg) noexcept -> void override {
         return T::handle_message(msg);
      }
   };

   union { internal_actor value; };
};


NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_STORAGE_H
