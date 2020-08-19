//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/actor/actor_handle.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>
#include <iostream>

NANO_CAF_NS_BEGIN

auto actor_handle::send_(message* msg) noexcept -> status_t {
   auto actor = ptr_->get();
   auto result = actor->enqueue(msg);
   switch(result) {
      case enq_result::ok:
         return status_t::ok;
      case enq_result::blocked:
         ptr_->context().schedule_job(*actor);
         return status_t::ok;
      case enq_result::closed:
         // msg has already been deleted by queue
         // so we don't need to worry about deleting it.
         return status_t::msg_queue_closed;
      case enq_result::null_msg:
         return status_t::null_msg;
      default:
         // should never be here.
         return status_t::failed;
   }
}

NANO_CAF_NS_END