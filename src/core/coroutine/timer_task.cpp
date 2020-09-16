//
// Created by Darwin Yuan on 2020/9/15.
//

#include <nano-caf/core/coroutine/timer_task.h>
#include <nano-caf/core/coroutine/coro_actor.h>

NANO_CAF_NS_BEGIN

///////////////////////////////////////////////////////////////////////
auto timer_task::stop_timer() noexcept -> void {
   if(self_ && self_->coroutines_.exists(handle_.address())) {
      handle_.promise().stop_timer();
   }
}

namespace detail {
   ///////////////////////////////////////////////////////////////////////
   auto timer_task_promise::get_return_object() -> timer_task {
      auto handle = handle_type::from_promise(*this);
      actor_.coroutines_.on_create(handle.address());
      return timer_task{actor_, handle};
   }

   ///////////////////////////////////////////////////////////////////////
   auto timer_task_promise::on_destroy() -> void {
      actor_.coroutines_.on_destroy(handle_type::from_promise(*this).address());
   }

   ///////////////////////////////////////////////////////////////////////
   auto timer_task_promise::stop_timer() noexcept -> void {
      if (awaiter_) {
         awaiter_->cancel(handle_type::from_promise(*this));
      }
   }

   inline auto timer_task_promise::still_waiting(timer_id_t id) -> bool {
      return (awaiter_ != nullptr) && awaiter_->matches(id);
   }
}

namespace detail {
   ///////////////////////////////////////////////////////////////////////
   auto timer_task_promise::timer_awaiter::await_suspend(handle_type caller) noexcept -> bool {
      result_ = start_timer(caller);
      return result_ == status_t::ok;
   }

   ///////////////////////////////////////////////////////////////////////
   auto timer_task_promise::timer_awaiter::start_timer(handle_type caller) noexcept -> status_t {
      auto& actor = caller.promise().actor_;
      auto result = actor.start_timer_(duration_, false,
         std::make_shared<timeout_callback_t>([=, &actor](timer_id_t id){
            // only if this coroutine is still alive & it's still waiting for this timer,
            // which might've been cancelled already.
            if(actor.coroutines_.exists(caller.address()) && caller.promise().still_waiting(id)) {
               caller();
            }
         }));

      if(result.is_ok()) {
         timer_id_ = *result;
         caller.promise().on_timer_start(this);
         caller_ = caller;
         return status_t::ok;
      }

      return result.failure();
   }

   auto timer_task_promise::timer_awaiter::await_resume() const noexcept -> status_t {
      caller_.promise().on_timer_done();
      return result_;
   }

   auto timer_task_promise::timer_awaiter::cancel(handle_type caller) -> void {
      caller.promise().actor_.stop_timer(*timer_id_);
      result_ = status_t::cancelled;
      caller.resume();
   }
}


NANO_CAF_NS_END