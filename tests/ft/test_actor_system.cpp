//
// Created by godsme on 7/29/20.
//
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/actor/actor.h>
#include <iostream>
#include "../ut/test_msgs.h"

using namespace NANO_CAF_NS;

using namespace std::chrono_literals;

struct my_actor : actor {
   timer_id_t timer_id_{300949};
   unsigned int times = 0;
   std::vector<int> values;

   auto handle_message(message& msg) noexcept -> task_result override {
      if (msg.msg_type_id_ == test_message::type_id ) {
         auto result = repeat(1s, [&]{
            std::cout << "timeout "  << std::endl;
            if(++times >= 5) {
               std::cout << "ready to stop" << std::endl;
               stop_timer(timer_id_);
               std::cout << "stop" << std::endl;
               exit(exit_reason::normal);
            }
         });
         if(result.is_ok()) {
            timer_id_ = *result;
         } else {
            std::cout << "start timer failed" << std::endl;
         }
      }
      return task_result::resume;
   }

    void clear() {
        values.clear();
    }
};

int main() {
    actor_system system;
    system.start(5);

    auto actor = system.spawn<my_actor>();

    actor.send<test_message>(1);
    actor.wait_for_exit();
    actor.release();

    system.shutdown();
}