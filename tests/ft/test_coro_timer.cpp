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
   auto echo_timer(int a) -> timer_task {
      co_await sleep(1s);
      spdlog::info("timeout");

      co_await sleep(2s);
      spdlog::info("timeout");
      exit(exit_reason::normal);
   }

   auto handle_message(message& msg) noexcept -> task_result override {
      if (msg.msg_type_id_ == test_message::type_id ) {
         echo_timer(0);
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