//
// Created by Darwin Yuan on 2020/9/15.
//

#ifndef NANO_CAF_TIMER_TASK_H
#define NANO_CAF_TIMER_TASK_H

#include <nano-caf/core/msg/predefined-msgs.h>
#include <nano-caf/core/coroutine/awaitable_trait.h>
#include <nano-caf/core/coroutine/actor_promise.h>
#include <nano-caf/core/coroutine/co_timer.h>
#include <nano-caf/core/coroutine/real_cancellable_timer_awaiter.h>
#include <nano-caf/core/coroutine/co_actor_final_awaiter.h>
#include <nano-caf/core/coroutine/co_task.h>
#include <nano-caf/util/caf_log.h>

NANO_CAF_NS_BEGIN

template<typename T>
struct timer_task;

namespace detail {
   struct timer_awaiter_keeper {
      inline auto on_timer_start(cancellable_timer_awaiter* timer) noexcept -> void {
         awaiter_ = timer;
      }
      inline auto on_timer_done() noexcept -> void {
         awaiter_ = nullptr;
      }
      auto still_waiting(timer_id_t) const noexcept -> bool;
      auto cancel() noexcept -> void;

   private:
      cancellable_timer_awaiter* awaiter_{nullptr};
   };

   template<typename T>
   struct timer_task_promise_base
      : actor_promise<timer_task_promise<T>> // must be the first
      , timer_awaiter_keeper {
      using super = actor_promise<timer_task_promise<T>>;
      using handle_type = std::coroutine_handle<timer_task_promise<T>>;
      template<typename ACTOR, typename ... Args>
      timer_task_promise_base(ACTOR& actor, Args const&...) noexcept
         : super{actor}
      {}

      auto get_return_object() noexcept -> timer_task<T>;
      auto initial_suspend() noexcept   -> std::suspend_never { return {}; }
      auto final_suspend() noexcept     -> co_actor_final_awaiter { return {}; }

      template<awaitable_concept<timer_task_promise<T>> AWAITABLE>
      auto await_transform(AWAITABLE&& awaitable) -> decltype(auto) {
         return get_awaiter(std::forward<AWAITABLE>(awaitable));
      }

      auto await_transform(co_timer&& timer) noexcept -> real_cancellable_timer_awaiter<T> {
         return timer.duration_;
      }
   };

   template<typename T>
   struct timer_task_promise : timer_task_promise_base<T> {
      using super = timer_task_promise_base<T>;
      using super::super;

      auto return_value(T&& value) noexcept {
         result_.template emplace<T>(std::forward<T>(value));
      }

      auto get_result() -> T&& {
         return std::move(*result_);
      }

   private:
      std::optional<T> result_{std::nullopt};
   };

   template<>
   struct timer_task_promise<void> : timer_task_promise_base<void> {
      using super = timer_task_promise_base<void>;
      using super::super;

      auto return_void() noexcept {}
   };
}

template<typename T = void>
struct timer_task
   : private co_task<detail::timer_task_promise<T>> {
   using promise_type = detail::timer_task_promise<T>;
   using handle_type = std::coroutine_handle<promise_type>;
   using super = co_task<promise_type>;

   using super::super;

private:
   friend struct awaiter;
   struct awaiter : private cancellable_timer_awaiter {
      awaiter(timer_task& self) : self_(self) {}

      auto await_ready() const noexcept -> bool { return !self_.is_valid(); }
      auto await_suspend(std::coroutine_handle<> caller) noexcept {
         self_.promise().save_caller(caller);
      }

      template<typename P>
      auto await_suspend(std::coroutine_handle<detail::timer_task_promise<P>> caller) noexcept {
         self_.promise().save_caller(caller);
         caller.promise().on_timer_start(this);
         timer_keeper_ = &caller.promise();
      }

      auto await_resume() const noexcept -> decltype(auto)
      requires std::same_as<T, void> {
         notify_caller_done();
      }

      auto await_resume() const noexcept -> decltype(auto)
      requires (!std::same_as<T, void>) {
         notify_caller_done();
         return self_.promise().get_result();
      }

   private:
      auto matches(timer_id_t id) const noexcept -> bool override {
         return self_.is_valid() && self_.promise().still_waiting(id);
      }

      auto cancel() noexcept -> void override {
         return self_.cancel();
      }

   private:
      auto notify_caller_done() const noexcept {
         if(timer_keeper_) timer_keeper_->on_timer_done();
      }

   private:
      timer_task& self_;
      detail::timer_awaiter_keeper* timer_keeper_{};
   };

public:
   auto operator co_await() -> awaiter { return *this; }
   auto cancel() noexcept -> void {
      // only by querying from the registry, we can precisely know
      // the aliveness of this coroutine.
      if(super::is_valid()) {
         super::promise().cancel();
      }
   }
};

namespace detail {
   template<typename T>
   auto timer_task_promise_base<T>::get_return_object() noexcept -> timer_task<T> {
      return timer_task<T>{ super::actor_,
                            handle_type::from_promise(*reinterpret_cast<timer_task_promise<T>*>(this))};
   }
}

NANO_CAF_NS_END

#endif //NANO_CAF_TIMER_TASK_H
