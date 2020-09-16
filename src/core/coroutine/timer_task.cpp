//
// Created by Darwin Yuan on 2020/9/15.
//

#include <nano-caf/core/coroutine/timer_task.h>
#include <nano-caf/core/coroutine/coro_actor.h>

NANO_CAF_NS_BEGIN

///////////////////////////////////////////////////////////////////////
auto timer_task::promise_type::get_return_object() -> timer_task {
   auto handle = handle_type::from_promise(*this);
   self_.coroutines_.on_create(handle.address());
   return timer_task{self_, handle};
}

///////////////////////////////////////////////////////////////////////
auto timer_task::promise_type::on_destroy() -> void {
   self_.coroutines_.on_destroy(handle_type::from_promise(*this).address());
}

///////////////////////////////////////////////////////////////////////
auto timer_task::timer_awaiter::await_suspend(handle_type caller) noexcept -> bool {
   return caller.promise().start_timer(spec_);
}

///////////////////////////////////////////////////////////////////////
auto timer_task::stop_timer() noexcept -> void {
   if(self_) {
      if(self_->coroutines_.exists(handle_.address())) {
         handle_.promise().stop_timer();
      }
   }
}

///////////////////////////////////////////////////////////////////////
auto timer_task::promise_type::start_timer(timer_spec const& spec) noexcept -> bool {
   auto caller = handle_type::from_promise(*this);
   auto result = self_.start_timer_(spec, false,
                                    std::make_shared<timeout_callback_t>( [=]{
                                       caller();
                                    }));
   if(result.failure()) {
      return false;
   }
   timer_id_ = *result;
   return true;
}

///////////////////////////////////////////////////////////////////////
auto timer_task::promise_type::stop_timer() noexcept -> void {
   if(timer_id_) {
      self_.stop_timer(*timer_id_);
   }
}

NANO_CAF_NS_END