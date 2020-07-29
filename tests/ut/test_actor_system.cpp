//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/msg/message_element.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/actor/actor.h>
#include <iostream>
#include <nano-caf/core/actor/behavior_based_actor.h>
#include "test_msgs.h"
#include <catch.hpp>
#include <nanobench.h>

namespace {
   using namespace NANO_CAF_NS;

   SCENARIO("a do-nothing actor system") {
      actor_system system;
      system.start(5);
      system.shutdown();
   }

   struct my_actor : actor {
      std::vector<size_t> values;
      auto handle_message(message_element& msg) noexcept -> task_result override {
         values.push_back(msg.body<test_message>()->value);
         return task_result::resume;
      }

      void clear() {
         values.clear();
      }
   };

   SCENARIO("actor system") {
      actor_system system;
      system.start(5);

      auto actor = system.spawn<my_actor>();

      actor.send<test_message>(1);
      actor.release();

      system.power_off();
   }

   constexpr size_t total_times = 100000;

   int pong_times = 0;
   struct pong_actor : actor {
      auto handle_message(message_element& msg) noexcept -> task_result override {
         switch(msg.get_id()) {
            case from_msg_type_to_id<test_message>::msg_id:
               reply<test_message>(msg.body<test_message>()->value);
               pong_times++;
               break;
            case from_msg_type_to_id<exit_msg>::msg_id:
               return task_result::stop_all;
         }
         return task_result::resume;
      }
   };

   struct ping_actor : actor {
      actor_handle pong;
      size_t times = 0;

      auto on_init() noexcept -> void override {
         pong = spawn<pong_actor>();
         send<test_message>(pong, 1);
         times = 1;
      }

      auto handle_message(message_element& msg) noexcept -> task_result override {
         switch(msg.get_id()) {
            case from_msg_type_to_id<test_message>::msg_id:
               times++;
               send<test_message>(pong, msg.body<test_message>()->value + 1);
               break;
            case from_msg_type_to_id<exit_msg>::msg_id:
               send<exit_msg>(pong, msg.body<exit_msg>()->reason);
               break;
            default:
               return task_result::skip;
         }
//         if(times++ < total_times ) {
//            send<test_message>(pong, msg.body<test_message>()->value + 1);
//         }
//         else {
//            exit(exit_reason::normal);
//         }

         return task_result::resume;
      }
   };

   SCENARIO("ping pang") {
      pong_times = 0;
      actor_system system;
      system.start(1);
      REQUIRE(system.get_num_of_actors() == 0);

      auto me = system.spawn<ping_actor>();
      REQUIRE(system.get_num_of_actors() == 2);
      std::this_thread::sleep_for(std::chrono::seconds {1});
      me.send<exit_msg>(exit_reason::user_shutdown);
      REQUIRE(me.wait_for_exit() == USER_SHUTDOWN);
      me.release();

      system.shutdown();
      //REQUIRE(pong_times == total_times);
      REQUIRE(system.get_num_of_actors() == 0);
   }

   struct future_actor : actor {
      int value = 10;
      unsigned long final_result = 0;

      auto add(int a, int b) {
         unsigned long result = 0;
         for(int i = 0; i < 1000000; i++) {
            result += (a * b + value);
         }

         return result;
      }

      auto on_init() noexcept -> void override {
         auto future1 = async(&future_actor::add, this, 5, 3);
         if(!future1) {
            exit(exit_reason::unhandled_exception);
         }

         auto future2 = async([this]() {
            size_t result = 0;
            int a = 20;
            int b = 4;
            for(int i = 0; i < 1000000; i++) {
               result += (a * b + value);
            }

            return result;
         });
         if(!future2) {
            exit(exit_reason::unhandled_exception);
         }

         auto result1 = with(future1)([this](unsigned long r1) {
            std::cout << "async future1 done = " << r1 << std::endl;
         });

         if(!result1) {
            exit(exit_reason::unhandled_exception);
         }

         auto result2 = with(future2)([this](unsigned long r2) {
            std::cout << "async future2 done = " << r2 << std::endl;
         });

         if(!result2) {
            exit(exit_reason::unhandled_exception);
         }

         auto result3 = with(future1, future2)([this](unsigned long r1, unsigned long r2) {
            //std::cout << "async done" << std::endl;
            final_result = r1 + r2;
            if(final_result == 115000000) {
               exit(exit_reason::normal);
            } else {
               exit(exit_reason::unknown);
            }
         });

         if(!result3) {
            exit(exit_reason::unhandled_exception);
         }
      }

      auto handle_message(message_element& msg) noexcept -> task_result override {
         //std::cout << "msg received" << std::endl;
         return task_result::resume;
      }
   };

   SCENARIO("async test") {
      actor_system system;
      system.start(1);

      auto me = system.spawn<future_actor>();
      me.send<test_message>(1);
      REQUIRE(me.wait_for_exit() == NORMAL_EXIT);
      me.release();

      system.shutdown();
      REQUIRE(system.get_num_of_actors() == 0);
   }

//   SCENARIO("future-calc benchmark") {
//      ankerl::nanobench::Bench().run("future calc", [&] {
//         actor_system system;
//         system.start(1);
//
//         auto me = system.spawn<future_actor>();
//         me.send<test_message>(1);
//         me.wait_for_exit();
//         me.release();
//
//         system.shutdown();
//      });
//   }

   int pong_times_2 = 0;
   struct pong_actor_1 : behavior_based_actor {
      auto get_behavior() -> behavior override {
         return {
            [&](test_message_atom, int value) {
               reply<test_message>(value);
               pong_times_2++;
            },
            [&](exit_msg_atom, exit_reason reason) {
               std::cout << "pong exit = " << (int)reason << std::endl;
            }
         };
      }
   };

   struct ping_actor_1 : behavior_based_actor {
      actor_handle pong;

      auto on_init() noexcept -> void override {
         pong = spawn<pong_actor_1>();
         send<test_message>(pong, 1);
      }

      auto get_behavior() -> behavior override {
         return {
            [&](test_message_atom, int value) {
               send<test_message>(pong, value + 1);
            },
            [&](exit_msg_atom, exit_reason reason) {
               send<exit_msg>(pong, reason);
               std::cout << "ping exit = " << (int)reason << std::endl;
            }
         };
      }
   };

   SCENARIO("ping pang 2") {
      pong_times = 0;
      actor_system system;
      system.start(1);
      REQUIRE(system.get_num_of_actors() == 0);

      auto me = system.spawn<ping_actor_1>();
      REQUIRE(system.get_num_of_actors() == 2);
      std::this_thread::sleep_for(std::chrono::seconds {1});
      me.send<exit_msg>(exit_reason::user_shutdown);
      REQUIRE(me.wait_for_exit() == USER_SHUTDOWN);
      me.release();

      system.shutdown();
      //REQUIRE(pong_times_2 == total_times);
      REQUIRE(system.get_num_of_actors() == 0);
   }
}