//
// Created by Darwin Yuan on 2020/9/15.
//

#ifndef NANO_CAF_TIMER_TASK_H
#define NANO_CAF_TIMER_TASK_H

#include <nano-caf/core/msg/predefined-msgs.h>
#include <nano-caf/core/coroutine/awaitable_trait.h>
#include <nano-caf/core/coroutine/co_timer.h>
#include <nano-caf/util/status_t.h>
#include <nano-caf/util/caf_log.h>
#include <coroutine>

NANO_CAF_NS_BEGIN

struct coro_actor;
struct timer_task;

namespace detail {
   struct timer_task_promise;
   struct cancellable_timer_awaiter {
      using handle_type = std::coroutine_handle<timer_task_promise>;

      cancellable_timer_awaiter(duration d) noexcept
         : duration_{d} {}

      auto await_ready() const noexcept { return false; }
      auto await_suspend(handle_type caller) noexcept -> bool;
      auto await_resume() const noexcept -> status_t;

      auto cancel(handle_type caller) noexcept -> void;
      auto matches(timer_id_t id) const noexcept -> bool {
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

   struct timer_awaiter_keeper {
      using handle_type = std::coroutine_handle<timer_task_promise>;
      inline auto on_timer_start(cancellable_timer_awaiter* timer) noexcept -> void {
         awaiter_ = timer;
      }
      inline auto on_timer_done() noexcept -> void {
         awaiter_ = nullptr;
      }
      auto still_waiting(timer_id_t) const noexcept -> bool;
      auto cancel(handle_type handle) noexcept -> void;
   private:
      cancellable_timer_awaiter* awaiter_{nullptr};
   };

   struct timer_task_promise : private timer_awaiter_keeper {
      using handle_type = std::coroutine_handle<timer_task_promise>;
   private:
      struct final_awaiter {
         auto await_ready() const noexcept { return false; }
         auto await_suspend(handle_type caller) noexcept -> bool;
         auto await_resume() const noexcept {};
      };

   public:
      template<typename ACTOR, typename ... Args>
      requires std::is_base_of_v<coro_actor, std::decay_t<ACTOR>>
      timer_task_promise(ACTOR& actor, Args const&...) noexcept
         : actor_{static_cast<coro_actor&>(actor)}
      {}

      auto get_return_object() noexcept -> timer_task;
      auto initial_suspend() noexcept -> std::suspend_never { return {}; }
      auto final_suspend() noexcept -> final_awaiter { return {}; }

      template<awaiter_concept AWAITER>
      auto await_transform(AWAITER&& awaiter) -> decltype(auto) {
         return std::forward<AWAITER>(awaiter);
      }

      auto await_transform(co_timer&& timer) noexcept -> cancellable_timer_awaiter {
         return timer.get_duration();
      }

      auto return_void() noexcept {}

      auto get_self_handle() const noexcept -> intrusive_actor_ptr;
      auto get_actor() const noexcept -> coro_actor& { return actor_; }

   private:
      auto stop_timer() noexcept -> void;
      auto on_destroy() noexcept -> void;

   private:
      friend cancellable_timer_awaiter;
      friend timer_task;

      coro_actor& actor_;
   };
}

struct timer_task {
   using promise_type = detail::timer_task_promise;
   using handle_type = std::coroutine_handle<promise_type>;

   timer_task() noexcept = default;
   explicit timer_task(coro_actor& actor, handle_type handle) noexcept
      : actor_{&actor}, handle_{handle} {}

   auto stop_timer() noexcept -> void;

private:
   coro_actor* actor_{};
   handle_type handle_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_TIMER_TASK_H
