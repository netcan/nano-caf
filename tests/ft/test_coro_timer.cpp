//
// Created by Darwin Yuan on 2020/9/16.
//

#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/coroutine/co_actor.h>
#include <nano-caf/core/coroutine/co_request.h>
#include <spdlog/spdlog.h>
#include "../ut/test_msgs.h"
#include <nano-caf/core/msg/request.h>
#include <nano-caf/core/actor/behavior_based_actor.h>

using namespace NANO_CAF_NS;

using namespace std::chrono_literals;

namespace {
   enum : uint32_t {
      media_session_interface_id = 1
   };

   __CAF_actor_interface(media_session, media_session_interface_id,
      (open,  (const long&) -> long),
      (close, (const long&) -> void),
      (empty, ()            -> std::shared_ptr<int>)
   );

   struct media_session_actor : behavior_based_actor {
      auto get_behavior() -> behavior override {
         return {
            [&](media_session::open, long value) -> long {
               return value + 1;
            },
            [&](media_session::close, long) {
            },
            [&](media_session::empty) -> auto {
               std::cout << "empty received" << std::endl;
               return std::make_shared<int>(1234);
            },
            [&](exit_msg_atom, exit_reason) {
               std::cout << "exit received" << std::endl;
            },
         };
      }
   };
}

struct my_actor : co_actor {
   typed_actor_handle<media_session> session_actor;
   auto on_init() -> void override {
      session_actor = spawn_typed_actor<media_session, media_session_actor>();
   }

   auto echo_timer() -> timer_task<int> {
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

      auto result_2 = co_await request<media_session::open>(session_actor, 100l);
      if(result_2.is_ok()) {
         spdlog::info("request result: {}", *result_2);
      } else {
         spdlog::error("request fail: {}", result_2.failure());
      }

      co_return 10;
   }

   auto wrapper_timer() -> timer_task<> {
      auto result = co_await echo_timer();
      spdlog::info("echo timer returns = {}", result);
      exit(exit_reason::normal);
   }

   auto handle_message(message& msg) noexcept -> task_result override {
      if (msg.msg_type_id_ == test_message::type_id ) {
         auto timer = wrapper_timer();
         timer.cancel_timer();
//         timer.cancel();
//         timer.cancel();
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