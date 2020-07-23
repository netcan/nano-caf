//
// Created by Darwin Yuan on 2020/7/23.
//

#ifndef NANO_CAF_ACTOR_CONTROL_BLOCK_H
#define NANO_CAF_ACTOR_CONTROL_BLOCK_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/cache_line_size.h>
#include <cstddef>
#include <atomic>

NANO_CAF_NS_BEGIN

struct sched_actor;

struct actor_control_block {
   using data_destructor = void (*)(sched_actor*);

   actor_control_block(data_destructor data_dtor)
      : strong_refs{1}, weak_refs{1}, data_dtor{data_dtor}
   {}

   actor_control_block(const actor_control_block&) = delete;
   actor_control_block& operator=(const actor_control_block&) = delete;

public:
   inline friend void intrusive_ptr_add_weak_ref(actor_control_block* x) {
      x->weak_refs.fetch_add(1, std::memory_order_relaxed);
   }

   inline friend void intrusive_ptr_add_ref(actor_control_block* x) {
      x->strong_refs.fetch_add(1, std::memory_order_relaxed);
   }

   friend void intrusive_ptr_release_weak(actor_control_block* x);
   friend void intrusive_ptr_release(actor_control_block* x);

   auto get() noexcept -> sched_actor* {
      return reinterpret_cast<sched_actor*>(reinterpret_cast<char*>(this) + CACHE_LINE_SIZE);
   }

   ~actor_control_block() noexcept = default;

private:
   std::atomic<size_t> strong_refs;
   std::atomic<size_t> weak_refs;
   const data_destructor data_dtor;
};





NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_CONTROL_BLOCK_H
