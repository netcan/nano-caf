//
// Created by Darwin Yuan on 2020/9/15.
//

#include <nano-caf/core/coroutine/timer_task.h>
#include <nano-caf/core/coroutine/coro_actor.h>

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
      auto handle = handle_type::from_promise(*this);

      // once this coroutine is created successfully, it should be registered
      // to the actor, so that its lifetime could be maintained automatically.
      actor_.coroutines_.on_create(handle);
      return timer_task{actor_, handle};
   }

   ///////////////////////////////////////////////////////////////////////
   auto timer_task_promise::on_destroy() noexcept -> void {
      actor_.coroutines_.on_destroy(handle_type::from_promise(*this));
   }

   ///////////////////////////////////////////////////////////////////////
   auto timer_task_promise::stop_timer() noexcept -> void {
      timer_awaiter_keeper::cancel();
   }

   auto timer_task_promise::get_self_handle() const noexcept -> intrusive_actor_ptr {
      return actor_.self_handle();
   }
}

namespace detail {
   auto timer_task_promise::final_awaiter::await_suspend(handle_type self) noexcept -> std::coroutine_handle<> {
      // before this coroutine is destroyed, it should be de-registered. so that
      // anyone who needs to know its aliveness (the timeout message, eg), is able
      // to get the precise result by querying the registry.
      self.promise().on_destroy();

      auto upper_caller = self.promise().get_caller();
      if(upper_caller) {
         return upper_caller;
      }

      // straight to the resume point, so that this coroutine could be destroyed.
      return std::noop_coroutine();
   }
}

namespace detail {
   ///////////////////////////////////////////////////////////////////////
   auto real_cancellable_timer_awaiter::await_suspend(handle_type caller) noexcept -> bool {
      result_ = start_timer(caller);
      // if this timer wasn't launched successfully, no suspend needed.
      return result_ == status_t::ok;
   }

   ///////////////////////////////////////////////////////////////////////
   auto real_cancellable_timer_awaiter::start_timer(handle_type caller) noexcept -> status_t {
      auto& actor = caller.promise().get_actor();
      auto result = actor.start_timer(duration_, false,
              std::make_shared<timeout_callback_t>([=, &actor](timer_id_t id) {
                 // only if this coroutine is still alive & it's still waiting for this timer,
                 // (which might've been cancelled already), the coroutine(caller) is resumed.
                 if (actor.coroutine_alive(caller) && caller.promise().still_waiting(id)) {
                    caller();
                 }
              }));

      if(result.is_ok()) {
         // remember the timer_id, and register this timer to the promise,
         // so that,
         // 1. it could be cancelled though promise;
         // 2. the timeout message could know if this timer is cancelled
         //    or not by querying the promise.
         timer_id_ = *result;
         caller.promise().on_timer_start(this);

         // we need to use this caller in await_resume.
         caller_ = caller;

         return status_t::ok;
      }

      return result.failure();
   }

   //////////////////////////////////////////////////////////////////////////////
   auto real_cancellable_timer_awaiter::await_resume() const noexcept -> status_t {
      // this function will be invoked if one of following conditions satisfied:
      // 1. this timer wasn't launched successfully;
      // 2. this awaiter is cancelled;
      // 3. the timeout message has been received.
      if(caller_) caller_.promise().on_timer_done();

      // return the result, succeeded or failed, to the coroutine.
      return result_;
   }

   //////////////////////////////////////////////////////////////////////////////
   auto real_cancellable_timer_awaiter::cancel() noexcept -> void {
      // as long as this function could be called, which means this timer
      // must've been started, and we haven't received its timeout msg yet.
      // (but the timeout message might've been in our mail box already).
      caller_.promise().get_actor().stop_timer(*timer_id_);
      result_ = status_t::cancelled;
      // since the timer has been cancelled, the caller should not
      // be suspend any longer. Once it's resumed, it will call
      // the await_resume of this awaiter immediately. So we don't
      // need to call its on_timer_done() here.
      caller_.resume();
   }
}


NANO_CAF_NS_END