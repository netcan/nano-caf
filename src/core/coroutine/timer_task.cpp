//
// Created by Darwin Yuan on 2020/9/15.
//

#include <nano-caf/core/coroutine/timer_task.h>
#include <nano-caf/core/coroutine/co_actor_context.h>

NANO_CAF_NS_BEGIN

namespace detail {
   //////////////////////////////////////////////////////////////////////////////
   auto timer_awaiter_keeper::still_waiting(timer_id_t id) const noexcept -> bool {
      return (awaiter_ != nullptr) && awaiter_->matches(id);
   }

   //////////////////////////////////////////////////////////////////////////////
   auto timer_awaiter_keeper::cancel() noexcept -> void {
      // only if the awaiter is not null, we are able to know a timer is still waiting,
      // although it might not be the one we intent to cancel (it doesn't matter actually).
      if (awaiter_) {
         awaiter_->cancel();
      }
   }
}

NANO_CAF_NS_END