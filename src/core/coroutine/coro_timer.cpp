//
// Created by Darwin Yuan on 2020/9/15.
//

#include <nano-caf/core/coroutine/coro_timer.h>
#include <nano-caf/core/coroutine/coro_actor.h>

NANO_CAF_NS_BEGIN

///////////////////////////////////////////////////////////////////////
auto coro_timer::timer_awaiter::await_suspend(handle_type caller) noexcept -> bool {
   return caller.promise().start_timer(self_, spec_);
}

///////////////////////////////////////////////////////////////////////
auto coro_timer::stop_timer() noexcept -> void {
   if(handle_) {
      handle_.promise().stop_timer();
   }
}

///////////////////////////////////////////////////////////////////////
auto coro_timer::promise_type::start_timer(coro_actor& self, timer_spec const& spec) noexcept -> bool {
   auto caller = handle_type::from_promise(*this);
   auto result = self.start_timer_(spec, false,
                                    std::make_shared<timeout_callback_t>( [=]{
                                       if(caller) caller();
                                    }));
   if(result.failure()) {
      return false;
   }
   timer_id_ = *result;
   self_ = &self;
   return true;
}

///////////////////////////////////////////////////////////////////////
auto coro_timer::promise_type::stop_timer() noexcept -> void {
   if(timer_id_) {
      self_->stop_timer(*timer_id_);
   }
}

NANO_CAF_NS_END