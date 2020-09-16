//
// Created by Darwin Yuan on 2020/9/15.
//

#ifndef NANO_CAF_CORO_ACTOR_H
#define NANO_CAF_CORO_ACTOR_H

#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/actor_context.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <nano-caf/core/actor/exit_reason.h>
#include <nano-caf/core/actor/typed_actor_handle.h>
#include <nano-caf/core/coroutine/coro_registry.h>
#include <nano-caf/core/coroutine/timer_task.h>

NANO_CAF_NS_BEGIN

struct coro_actor : actor_context {
   inline auto stop_timer(timer_id_t timer_id) -> void {
      get_system_actor_context().stop_timer(self_handle(), timer_id);
   }

   template<typename Rep, typename Period>
   inline auto start_timer(std::chrono::duration<Rep, Period> const& d, bool periodic = false) -> result_t<timer_id_t> {
      return start_timer((uint64_t)std::chrono::microseconds(d).count(), periodic);
   }

   inline auto start_timer(timer_spec&& spec, bool periodic = false) -> result_t<timer_id_t> {
      return start_timer_(spec, periodic, nullptr);
   }

   template<typename Rep, typename Period>
   auto sleep(std::chrono::duration<Rep, Period> const& d) {
      return timer_task::timer_awaiter{(uint64_t)std::chrono::microseconds(d).count()};
   }

private:
   friend struct timer_task::promise_type;
   auto start_timer_(timer_spec const& spec, bool periodic, std::shared_ptr<timeout_callback_t> callback) -> result_t<timer_id_t> {
      auto result = get_system_actor_context().start_timer(self_handle(), spec, periodic, std::move(callback));
      if(result.is_ok()) {
         on_timer_created();
      }
      return result;
   }

   friend timer_task;
   coro_registry coroutines_;

private:
   inline auto self_handle() const noexcept -> intrusive_actor_ptr override { return &self(); }
   inline auto get_system_actor_context() -> system_actor_context& override { return self().context(); }
   virtual auto self() const noexcept -> actor_control_block& = 0;
   virtual auto current_sender() const noexcept -> actor_handle = 0;
   virtual auto on_timer_created() -> void = 0;
   virtual auto register_future_callback(future_callback* future) noexcept -> status_t = 0;

protected:
   virtual auto on_init() -> void {}
   virtual auto on_exit() -> void {}
   virtual auto handle_message(message&) noexcept -> task_result {
      return task_result::done;
   }
   virtual auto exit(exit_reason) noexcept -> void = 0;
};

NANO_CAF_NS_END

#endif //NANO_CAF_CORO_ACTOR_H
