//
// Created by Darwin Yuan on 2020/9/23.
//

#include <nano-caf/core/await/abstract_future_awaiter.h>

NANO_CAF_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////////////////////////////
auto abstract_future_awaiter::cancel(status_t cause) noexcept -> void {
   if(destroyed_) return;
   on_fail(cause);
   destroy();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
auto abstract_future_awaiter::destroy() -> void {
      context_.remove_awaiter(this);
   if(timer_id_.has_value()) {
      context_.stop_timer(*timer_id_);
      timer_id_ = std::nullopt;
   }
   destroyed_ = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
auto abstract_future_awaiter::await(uint64_t duration, std::weak_ptr<awaiter> ptr) noexcept -> status_t {
   auto result = start_timer_(duration, ptr);
   if(result != status_t::ok) {
      cancel(result);
   }
   return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
auto abstract_future_awaiter::start_timer_(uint64_t duration, std::weak_ptr<awaiter> ptr) noexcept -> status_t {
   if(destroyed_ || timer_id_.has_value()) return status_t::ok;
   auto cb = std::make_shared<timeout_callback_t>([obj = ptr](auto){
      auto cancellable = obj.lock();
      if(cancellable) {
         cancellable->timeout();
      }
   });
   if(cb == nullptr) {
      return status_t::out_of_mem;
   }

   auto result = context_.start_timer(duration, false, cb);
   if(result.is_ok()) {
      timer_id_ = *result;
   }

   return result.failure();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
auto abstract_future_awaiter::timeout() noexcept -> void {
   timer_id_ = std::nullopt;
   cancel(status_t::timeout);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
auto abstract_future_awaiter::on_future_fail(status_t cause) noexcept -> void {
   if (!destroyed_) {
      on_fail(cause);
      destroy();
   }
}

NANO_CAF_NS_END