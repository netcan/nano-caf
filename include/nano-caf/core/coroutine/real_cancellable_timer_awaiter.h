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

template<typename T>
struct timer_task_promise;

template<typename T>
struct real_cancellable_timer_awaiter : cancellable_timer_awaiter {
   using handle_type = std::coroutine_handle<timer_task_promise<T>>;
   real_cancellable_timer_awaiter(duration d) noexcept
      : duration_{d} {}

   auto await_ready() const noexcept { return false; }
   auto await_suspend(handle_type caller) noexcept -> bool {
      result_ = start_timer(caller);
      // if this timer wasn't launched successfully, no suspend needed.
      return result_ == status_t::ok;
   }
   auto await_resume() const noexcept -> status_t {
      // this function will be invoked if one of following conditions satisfied:
      // 1. this timer wasn't launched successfully;
      // 2. this awaiter is cancelled;
      // 3. the timeout message has been received.
      if(caller_) caller_.promise().on_timer_done();

      // return the result, succeeded or failed, to the coroutine.
      return result_;
   }

private:
   auto cancel() noexcept -> void override {
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

   auto matches(timer_id_t id) const noexcept -> bool override {
      return timer_id_ && (*timer_id_ == id);
   }

private:
   auto start_timer(handle_type caller) noexcept -> status_t {
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

private:
   duration duration_;
   std::optional<timer_id_t> timer_id_{std::nullopt};
   status_t result_{status_t::ok};
   handle_type caller_;
};

} NANO_CAF_NS_END

#endif //NANO_CAF_REAL_CANCELLABLE_TIMER_AWAITER_H
