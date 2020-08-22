//
// Created by godsme on 7/29/20.
//
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/actor/actor.h>
#include "../ut/test_msgs.h"

using namespace NANO_CAF_NS;

using namespace std::chrono_literals;

struct my_actor : actor {
   timer_id timer_id_ = 300949;
   unsigned int times = 0;
    std::vector<int> values;
    auto handle_message(message& msg) noexcept -> task_result override {
       std::cout << "received a message" << std::endl;
       switch (msg.msg_type_id_) {
          case test_message::type_id: {
             std::cout << "start timer : " << test_message::type_id << std::endl;
             auto status = start_timer({1, timer_unit::seconds}, true)
                .with_value([this](auto timer_id) {
                   timer_id_ = timer_id;
                   return status_t::ok;
                });
             if (status != status_t::ok) {
                std::cout << "start timer failed" << std::endl;
             }
             break;
          }
          case timeout_msg::type_id:
             std::cout << "timeout : " << timeout_msg::type_id << std::endl;
             if(times++ >= 5) {
                std::cout << "ready to stop" << std::endl;
                stop_timer(timer_id_);
                std::this_thread::sleep_for(1s);
                std::cout << "stop" << std::endl;
                exit(exit_reason::normal);
             }

             break;
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