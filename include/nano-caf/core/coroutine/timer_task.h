//
// Created by Darwin Yuan on 2020/9/15.
//

#ifndef NANO_CAF_TIMER_TASK_H
#define NANO_CAF_TIMER_TASK_H

#include <nano-caf/core/msg/predefined-msgs.h>
#include <nano-caf/util/caf_log.h>
#include <coroutine>

NANO_CAF_NS_BEGIN

struct coro_actor;

struct timer_task {
   struct promise_type;
   using handle_type = std::coroutine_handle<promise_type>;

   struct timer_awaiter {
      timer_awaiter(timer_spec const& spec)
         : spec_{spec} {}

      auto await_ready() const noexcept { return false; }
      auto await_suspend(handle_type caller) noexcept -> bool;
      void await_resume() const noexcept {}

   private:
      timer_spec spec_;
   };

   template<typename T> struct S;
   struct promise_type {
      template<typename ACTOR, typename ... Args>
      requires std::is_base_of_v<coro_actor, std::decay_t<ACTOR>>
      promise_type(ACTOR& self, Args const&...)
         : self_{static_cast<coro_actor&>(self)}
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

      auto return_void() {}

      auto start_timer(timer_spec const&) noexcept -> bool;
      auto stop_timer() noexcept -> void;
      auto on_destroy() -> void;

   private:
      std::optional<timer_id_t> timer_id_;
      coro_actor& self_;
   };

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
