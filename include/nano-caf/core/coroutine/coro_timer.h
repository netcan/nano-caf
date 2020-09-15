//
// Created by Darwin Yuan on 2020/9/15.
//

#ifndef NANO_CAF_CORO_TIMER_H
#define NANO_CAF_CORO_TIMER_H

#include <nano-caf/core/msg/predefined-msgs.h>
#include <coroutine>

NANO_CAF_NS_BEGIN

struct coro_actor;

struct coro_timer {
   struct promise_type;
   using handle_type = std::coroutine_handle<promise_type>;

   struct timer_awaiter {
      timer_awaiter(coro_actor& self, timer_spec const& spec)
         : self_{self}, spec_{spec} {}

      auto await_ready() const noexcept { return false; }
      auto await_suspend(handle_type caller) noexcept -> bool;
      void await_resume() const noexcept {}

   private:
      coro_actor& self_;
      timer_spec spec_;
   };

   struct promise_type {
      auto get_return_object() {
         return coro_timer{ handle_type::from_promise(*this)};
      }

      auto initial_suspend() {
         return std::suspend_never{};
      }

      auto final_suspend() {
         return std::suspend_never{};
      }

      auto return_void() {}

      auto start_timer(coro_actor& self, timer_spec const&) noexcept -> bool;
      auto stop_timer() noexcept -> void;

   private:
      std::optional<timer_id_t> timer_id_;
      coro_actor* self_{};
   };

   coro_timer() = default;
   explicit coro_timer(handle_type handle) noexcept : handle_{handle} {}

   auto stop_timer() noexcept -> void;

   coro_timer(coro_timer const&) = delete;
   coro_timer(coro_timer&& rhs) : handle_{rhs.handle_} {
      rhs.handle_ = nullptr;
   }

   auto operator=(coro_timer const&) noexcept -> coro_timer& = delete;
   auto operator=(coro_timer&& rhs) noexcept -> coro_timer& {
      std::exchange(rhs.handle_, handle_);
      return *this;
   }

   ~coro_timer() {
      if(handle_) handle_.destroy();
   }
private:
   handle_type handle_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_CORO_TIMER_H
