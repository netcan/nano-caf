//
// Created by Darwin Yuan on 2020/9/15.
//

#ifndef NANO_CAF_TIMER_TASK_H
#define NANO_CAF_TIMER_TASK_H

#include <nano-caf/core/msg/predefined-msgs.h>
#include <nano-caf/util/status_t.h>
#include <nano-caf/util/caf_log.h>
#include <coroutine>

NANO_CAF_NS_BEGIN

struct coro_actor;
struct timer_task;

struct co_timer {
   duration duration_;
};

namespace detail {

   struct timer_task_promise {
      using handle_type = std::coroutine_handle<timer_task_promise>;

   private:
      struct timer_awaiter {
         timer_awaiter(duration d)
            : duration_{d} {}

         auto await_ready() const noexcept { return false; }
         auto await_suspend(handle_type caller) noexcept -> bool;
         auto await_resume() const noexcept -> status_t;

         auto cancel(handle_type caller) -> void;
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

   public:
      template<typename ACTOR, typename ... Args>
      requires std::is_base_of_v<coro_actor, std::decay_t<ACTOR>>
      timer_task_promise(ACTOR& actor, Args const&...)
         : actor_{static_cast<coro_actor&>(actor)}
      {}

      auto get_return_object() -> timer_task;

      auto initial_suspend() {
         return std::suspend_never{};
      }

      auto final_suspend() {
         struct final_awaiter {
            auto await_ready() const noexcept { return false; }
            auto await_suspend(handle_type caller) noexcept -> bool {
               caller.promise().on_destroy();
               return false;
            }
            void await_resume() const noexcept {}
         };

         return final_awaiter{};
      }

      auto await_transform(co_timer const& timer) -> timer_awaiter {
         return timer.duration_;
      }

      auto return_void() {}

      auto stop_timer() noexcept -> void;
      auto on_destroy() -> void;

   private:
      inline auto on_timer_start(timer_awaiter* timer) -> void {
         awaiter_ = timer;
      }
      inline auto on_timer_done() -> void {
         awaiter_ = nullptr;
      }
      inline auto still_waiting(timer_id_t) -> bool;
   private:
      coro_actor& actor_;
      timer_awaiter* awaiter_{nullptr};
   };
}

struct timer_task {
   using promise_type = detail::timer_task_promise;
   using handle_type = std::coroutine_handle<promise_type>;

   timer_task() = default;
   explicit timer_task(coro_actor& self, handle_type handle) noexcept
      : self_{&self}, handle_{handle} {}

   auto stop_timer() noexcept -> void;

   timer_task(timer_task const&) = default;
   timer_task(timer_task&& rhs) = default;

   auto operator=(timer_task const&) noexcept -> timer_task& = default;
   auto operator=(timer_task&& rhs) noexcept -> timer_task& = default;

   ~timer_task() = default;

private:
   coro_actor* self_{};
   handle_type handle_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_TIMER_TASK_H
