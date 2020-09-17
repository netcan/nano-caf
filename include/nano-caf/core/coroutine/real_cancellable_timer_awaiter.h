//
// Created by Darwin Yuan on 2020/9/17.
//

#ifndef NANO_CAF_REAL_CANCELLABLE_TIMER_AWAITER_H
#define NANO_CAF_REAL_CANCELLABLE_TIMER_AWAITER_H

#include <nano-caf/core/coroutine/cancellable_timer_awaiter.h>
#include <nano-caf/core/timer/duration.h>
#include <nano-caf/util/status_t.h>
#include <coroutine>

NANO_CAF_NS_BEGIN namespace detail {

struct timer_task_promise;

struct real_cancellable_timer_awaiter : cancellable_timer_awaiter {
   using handle_type = std::coroutine_handle<timer_task_promise>;
   real_cancellable_timer_awaiter(duration d) noexcept
      : duration_{d} {}

   auto await_ready() const noexcept { return false; }
   auto await_suspend(handle_type caller) noexcept -> bool;
   auto await_resume() const noexcept -> status_t;

private:
   auto cancel() noexcept -> void override;
   auto matches(timer_id_t id) const noexcept -> bool override {
      return timer_id_ && (*timer_id_ == id);
   }

private:
   auto start_timer(handle_type caller) noexcept -> status_t;

private:
   duration duration_;
   std::optional<timer_id_t> timer_id_{std::nullopt};
   status_t result_{status_t::ok};
   handle_type caller_;
};

} NANO_CAF_NS_END

#endif //NANO_CAF_REAL_CANCELLABLE_TIMER_AWAITER_H
