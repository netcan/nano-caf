//
// Created by Darwin Yuan on 2020/9/15.
//

#include <nano-caf/core/coroutine/timer_task.h>
#include <nano-caf/core/coroutine/co_actor_context.h>

NANO_CAF_NS_BEGIN

///////////////////////////////////////////////////////////////////////
auto timer_task::is_valid() const noexcept -> bool {
   return handle_ && actor_ && actor_->coroutine_alive(handle_);
}

///////////////////////////////////////////////////////////////////////
auto timer_task::cancel() noexcept -> void {
   // only by querying from the registry, we can precisely know
   // the aliveness of this coroutine.
   if(is_valid()) {
      handle_.promise().stop_timer();
   }
}

///////////////////////////////////////////////////////////////////////
auto timer_task::matches(timer_id_t id) const noexcept -> bool {
   return is_valid() && handle_.promise().still_waiting(id);
}

//////////////////////////////////////////////////////////////////////////////
auto timer_task::await_suspend(std::coroutine_handle<> caller) noexcept -> bool {
   handle_.promise().save_caller(caller);
   return true;
}

//////////////////////////////////////////////////////////////////////////////
auto timer_task::await_suspend(handle_type caller) noexcept -> bool {
   handle_.promise().save_caller(caller);
   caller.promise().on_timer_start(this);
   caller_ = caller;
   return true;
}

//////////////////////////////////////////////////////////////////////////////
auto timer_task::await_resume() const noexcept -> void{
   if(caller_) caller_.promise().on_timer_done();
}

namespace detail {
   //////////////////////////////////////////////////////////////////////////////
   inline auto timer_awaiter_keeper::still_waiting(timer_id_t id) const noexcept -> bool {
      return (awaiter_ != nullptr) && awaiter_->matches(id);
   }

   //////////////////////////////////////////////////////////////////////////////
   inline auto timer_awaiter_keeper::cancel() noexcept -> void {
      // only if the awaiter is not null, we are able to know a timer is still waiting,
      // although it might not be the one we intent to cancel (it doesn't matter actually).
      if (awaiter_) {
         awaiter_->cancel();
      }
   }
}

namespace detail {
   ///////////////////////////////////////////////////////////////////////
   auto timer_task_promise::get_return_object() noexcept -> timer_task {
      return timer_task{actor_, handle_type::from_promise(*this)};
   }

   ///////////////////////////////////////////////////////////////////////
   auto timer_task_promise::stop_timer() noexcept -> void {
      timer_awaiter_keeper::cancel();
   }

   auto timer_task_promise::get_self_handle() const noexcept -> intrusive_actor_ptr {
      return actor_.self_handle();
   }
}

NANO_CAF_NS_END