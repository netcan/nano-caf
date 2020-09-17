//
// Created by Darwin Yuan on 2020/9/17.
//

#ifndef NANO_CAF_CO_ACTOR_H
#define NANO_CAF_CO_ACTOR_H

#include <nano-caf/core/coroutine/co_actor_context.h>
#include <nano-caf/core/coroutine/timer_task.h>

NANO_CAF_NS_BEGIN

struct co_actor : co_actor_context {
   template<typename Rep, typename Period>
   [[nodiscard("co_await")]] auto sleep(std::chrono::duration<Rep, Period> const& d) {
      return co_timer{(uint64_t)std::chrono::microseconds(d).count()};
   }

protected:
   virtual auto on_init() -> void {}
   virtual auto on_exit() -> void {}
   virtual auto handle_message(message&) noexcept -> task_result {
      return task_result::done;
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_CO_ACTOR_H
