//
// Created by Darwin Yuan on 2020/9/16.
//

#include <nano-caf/core/actor/intrusive_actor_ptr.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/util/likely.h>

NANO_CAF_NS_BEGIN

auto intrusive_actor_ptr::send(message* msg) noexcept -> status_t {
   if(__unlikely(!(*this))) {
      return status_t::null_pointer;
   }

   auto actor = (*this)->get();
   auto result = actor->enqueue(msg);
   switch(result) {
      case enq_result::ok:
         return status_t::ok;
      case enq_result::blocked:
         (*this)->context().schedule_job(*actor);
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