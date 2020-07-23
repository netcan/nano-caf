//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_ACTOR_STORAGE_H
#define NANO_CAF_ACTOR_STORAGE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/message_element.h>
#include <nano-caf/core/lifo_inbox.h>
#include <nano-caf/core/actor_control_block.h>

NANO_CAF_NS_BEGIN

template<typename T>
struct actor_storage  {
   template<typename ... Ts>
   actor_storage(Ts&& ... args) : control{data_dtor, block_dtor} {
      new (&value) T(std::forward<Ts...>(args...));
   }

private:
   static void data_dtor(sched_actor* ptr) {
      static_cast<T*>(ptr)->~T();
   }

   static void block_dtor(actor_control_block* ptr) {
      delete reinterpret_cast<actor_storage*>(ptr);
   }
private:
   static_assert(sizeof(actor_control_block) <= CACHE_LINE_SIZE);
   actor_control_block control;
   char padding[CACHE_LINE_SIZE - sizeof(control)];
   union { T value; };
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_STORAGE_H
