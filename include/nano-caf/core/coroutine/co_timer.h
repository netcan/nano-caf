//
// Created by Darwin Yuan on 2020/9/17.
//

#ifndef NANO_CAF_CO_TIMER_H
#define NANO_CAF_CO_TIMER_H

#include <nano-caf/core/msg/predefined-msgs.h>
#include <nano-caf/util/status_t.h>
#include <coroutine>

NANO_CAF_NS_BEGIN

namespace detail {
   struct co_timer_awaiter {
      co_timer_awaiter(duration d) : duration_{d} {}

      auto await_ready() const noexcept { return false; }

      template<typename P>
      auto await_suspend(std::coroutine_handle<P> caller) noexcept -> bool {
         auto& actor = caller.promise().get_actor();
         auto result = actor.start_timer(duration_, false,
              std::make_shared<timeout_callback_t>([=, &actor](timer_id_t) {
                 if (actor.coroutine_alive(caller)) {
                    caller();
                 }
              }));

         if(result.is_ok()) {
            result_ = status_t::ok;
            return true;
         } else {
            result_ = result.failure();
            return false;
         }
      }

      auto await_resume() const noexcept -> status_t { return result_; }

   private:
      duration duration_;
      status_t result_{status_t::ok};
   };
}

struct co_timer {
   auto operator co_await () -> detail::co_timer_awaiter { return duration_; }
   duration duration_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_CO_TIMER_H
