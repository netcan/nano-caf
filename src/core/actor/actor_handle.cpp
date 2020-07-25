//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/actor/actor_handle.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>

NANO_CAF_NS_BEGIN

auto actor_handle::send_(message_element* msg) noexcept -> enq_result {
   if(msg == nullptr) return enq_result::null_msg;

   auto actor = ptr_->get<sched_actor>();
   auto result = actor->enqueue(msg);
   switch(result) {
      case enq_result::blocked:
         ptr_->system().schedule_job(*actor);
         return enq_result::ok;
      default:
         return result;
   }
}

NANO_CAF_NS_END