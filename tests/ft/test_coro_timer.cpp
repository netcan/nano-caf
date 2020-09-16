//
// Created by Darwin Yuan on 2020/9/16.
//

#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/coroutine/coro_actor.h>
#include <spdlog/spdlog.h>
#include "../ut/test_msgs.h"

using namespace NANO_CAF_NS;

using namespace std::chrono_literals;

struct my_actor : coro_actor {
   auto echo_timer() -> timer_task {
      auto result = co_await sleep(1s);
      if(result == status_t::ok) {
         spdlog::info("timeout 1");
      } else {
         spdlog::error("timer 1 failed: {}", result);
      }

      result = co_await sleep(1s);
      if(result == status_t::ok) {
         spdlog::info("timeout 2");
      } else {
         spdlog::error("timer 2 failed: {}", result);
      }

      exit(exit_reason::normal);
   }

   auto handle_message(message& msg) noexcept -> task_result override {
      if (msg.msg_type_id_ == test_message::type_id ) {
         auto timer = echo_timer();
         timer.stop_timer();
//         timer.stop_timer();
//         timer.stop_timer();
      }
      return task_result::resume;
   }
};

int main() {
   actor_system system;
   system.start(5);

   auto actor = system.spawn<my_actor>();

   actor.send<test_message>(1);
   actor.wait_for_exit();
   actor.release();

   spdlog::info("shutdown");
   system.shutdown();
}