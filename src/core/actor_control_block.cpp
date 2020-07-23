//
// Created by Darwin Yuan on 2020/7/23.
//

#include <nano-caf/core/actor_control_block.h>

NANO_CAF_NS_BEGIN

void intrusive_ptr_release_weak(actor_control_block* x) {
   if (x->weak_refs == 1
       || x->weak_refs.fetch_sub(1, std::memory_order_acq_rel) == 1)
      x->~actor_control_block();
}

void intrusive_ptr_release(actor_control_block* x) {
   if (x->strong_refs.fetch_sub(1, std::memory_order_acq_rel) == 1) {
      x->data_dtor(x->get());
      intrusive_ptr_release_weak(x);
   }
}

NANO_CAF_NS_END
