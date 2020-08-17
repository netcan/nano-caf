//
// Created by godsme on 7/29/20.
//
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/actor/actor.h>
#include <iostream>
#include <nano-caf/core/actor/behavior_based_actor.h>
#include "../ut/test_msgs.h"

using namespace NANO_CAF_NS;

int pong_times_2 = 0;
struct pong_actor_1 : behavior_based_actor {
    auto get_behavior() -> behavior override {
        return {
            [&](shared_buf_msg_atom, std::shared_ptr<big_msg> msg) {
                reply<shared_buf_msg>(msg);
                pong_times_2++;
            },
            [&](exit_msg_atom, exit_reason) {
            }
        };
    }
};

struct ping_actor_1 : behavior_based_actor {
    actor_handle pong;

    auto on_init() noexcept -> void override {
        pong = spawn<pong_actor_1>();
        send<shared_buf_msg>(pong, std::make_shared<big_msg>());
    }

    auto get_behavior() -> behavior override {
        return {
                [&](shared_buf_msg_atom, std::shared_ptr<big_msg>) {
                    send<shared_buf_msg>(pong, std::make_shared<big_msg>());
                },
                [&](exit_msg_atom, exit_reason reason) {
                    send<exit_msg>(pong, reason);
                }
        };
    }
};

auto run(size_t num_of_worker) {
   pong_times_2 = 0;

   actor_system system;
   system.start(num_of_worker);

   auto me = system.spawn<ping_actor_1>();
   std::this_thread::sleep_for(std::chrono::seconds {1});
   me.send<exit_msg>(exit_reason::user_shutdown);
   me.wait_for_exit();
   me.release();

   system.shutdown();

   std::cout << "[" << num_of_worker << " threads] ping pong times = " << pong_times_2 * 2 << std::endl;

   for(size_t i=0; i<num_of_worker; i++) {
      std::cout << "worker[" <<i<<"] = " << system.sched_jobs(i) << " jobs" << std::endl;
   }
}

int main() {
   run(1);
   run(2);
   run(3);
   run(4);
   run(5);
}