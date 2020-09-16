//
// Created by Darwin Yuan on 2020/9/15.
//

#ifndef NANO_CAF_CORO_TIMER_H
#define NANO_CAF_CORO_TIMER_H

#include <nano-caf/core/msg/predefined-msgs.h>
#include <nano-caf/util/caf_log.h>
#include <coroutine>

NANO_CAF_NS_BEGIN

struct coro_actor;

struct [[nodiscard]] coro_timer {
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

private:


public:
   template<typename T> struct S;
   struct promise_type {
      template<typename ACTOR, typename ... Args>
      requires std::is_base_of_v<coro_actor, std::decay_t<ACTOR>>
      promise_type(ACTOR& self, Args const&...)
         : self_{static_cast<coro_actor&>(self)}
      {}

      auto get_return_object() -> coro_timer;

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

   coro_timer() = default;
   explicit coro_timer(coro_actor& self, handle_type handle) noexcept
      : self_{&self}, handle_{handle} {}

   auto stop_timer() noexcept -> void;

   coro_timer(coro_timer const&) = default;
   coro_timer(coro_timer&& rhs) = default;

   auto operator=(coro_timer const&) noexcept -> coro_timer& = default;
   auto operator=(coro_timer&& rhs) noexcept -> coro_timer& = default;

   ~coro_timer() = default;

private:
   coro_actor* self_{};
   handle_type handle_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_CORO_TIMER_H
