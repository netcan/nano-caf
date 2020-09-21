//
// Created by godsme on 7/29/20.
//
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <nano-caf/core/actor/behavior_based_actor.h>
#include "../ut/test_msgs.h"

using namespace NANO_CAF_NS;

CAF_def_message(forward_msg,
                (actor,     actor_handle));

constexpr size_t total_actors = 20;
size_t pong_times[total_actors] = {0};

struct pong_actor_1 : behavior_based_actor {
   pong_actor_1(size_t i) : index(i) {}

    auto get_behavior() -> behavior override {
        return {
            [&](forward_msg_atom, actor_handle actor) {
                send<shared_buf_msg>(actor, std::make_shared<big_msg>());
                pong_times[index]++;
            },
            [&](shared_buf_msg_atom, std::shared_ptr<big_msg> msg) {
               reply<shared_buf_msg>(msg);
               pong_times[index]++;
            },
            [&](exit_msg_atom, exit_reason) {
            }
        };
    }
   size_t index;
};

using namespace std::chrono_literals;

size_t ping_times = 0;
struct ping_actor_1 : behavior_based_actor {
    actor_handle pong[total_actors];
    size_t n = 1;

    auto on_init() noexcept -> void override {
       for(size_t i=0; i<total_actors; i++) {
          pong[i] = spawn<pong_actor_1>(i);
       }

//       for(size_t i=0; i<total_actors; i++) {
//          send<shared_buf_msg>(pong[i], std::make_shared<big_msg>());
//       }

       repeat(1ms, [&]{
          for(size_t i=0; i<total_actors; i++) {
             send<forward_msg>(pong[i], pong[(i+n) % total_actors]);
          }
          if(++n == total_actors) {
             n = 1;
          }
       });
    }

    auto get_behavior() -> behavior override {
        return {
                [&](shared_buf_msg_atom, std::shared_ptr<big_msg>) {
                   reply<shared_buf_msg>(std::make_shared<big_msg>());
                   ping_times++;
                },
                [&](exit_msg_atom, exit_reason reason) {
                   for(size_t i=0; i<total_actors; i++) {
                      pong[i].exit_and_release(reason);
                   }
                }
        };
    }
};

auto run(size_t num_of_worker) {
   ping_times = 0;
   for(size_t i=0; i<total_actors; i++) {
      pong_times[i] = 0;
   }

   actor_system system{num_of_worker};

   auto me = system.spawn<ping_actor_1>();
   std::this_thread::sleep_for(std::chrono::seconds {1});
   me.send<exit_msg>(exit_reason::user_shutdown);
   me.wait_for_exit();
   me.release();

   system.shutdown();

   size_t total = ping_times;
   for(size_t i=0; i<total_actors; i++) {
      total += pong_times[i];
   }

   std::cout << "[" << num_of_worker << " threads] ping pong times = "
      << total << std::endl;

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
   run(6);
   run(7);
   run(8);
   run(9);
   run(10);
}