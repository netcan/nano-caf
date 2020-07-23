//
// Created by Darwin Yuan on 2020/7/23.
//

#include <nano-caf/core/actor_control_block.h>

NANO_CAF_NS_BEGIN

auto intrusive_ptr_release_weak(actor_control_block* x) noexcept -> void {
   if (x->weak_refs == 1
       || x->weak_refs.fetch_sub(1, std::memory_order_acq_rel) == 1)
      x->block_dtor(x);
}

auto intrusive_ptr_release(actor_control_block* x) noexcept -> void {
   if (x->strong_refs.fetch_sub(1, std::memory_order_acq_rel) == 1) {
      x->data_dtor(x->get());
      intrusive_ptr_release_weak(x);
   }
}

auto intrusive_ptr_upgrade_weak(actor_control_block* x) noexcept -> intrusive_actor_ptr {
   auto count = x->strong_refs.load();
   while (count != 0) {
      if (x->strong_refs.compare_exchange_weak(count, count + 1,
                                               std::memory_order_relaxed)) {
         return {x, false};
      }
   }

   return nullptr;
}

NANO_CAF_NS_END
