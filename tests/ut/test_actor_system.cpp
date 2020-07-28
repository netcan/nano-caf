//
// Created by Darwin Yuan on 2020/7/24.
//

#include <catch.hpp>
#include <nano-caf/core/msg/message_element.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/actor/actor.h>
#include <iostream>

namespace {
   using namespace NANO_CAF_NS;

   struct my_message  {
      my_message(uint32_t value)
         : value{value} {}

      uint32_t value{};
   };

   SCENARIO("a do-nothing actor system") {
      actor_system system;
      system.start(5);
      system.shutdown();
   }

   struct my_actor : actor {
      std::vector<size_t> values;
      auto handle_message(const message_element& msg) noexcept -> void override {
         values.push_back(msg.body<my_message>()->value);
      }

      void clear() {
         values.clear();
      }
   };

   SCENARIO("actor system") {
      actor_system system;
      system.start(5);

      auto actor = system.spawn<my_actor>();

      actor.send<my_message>({1}, 1);

      system.power_off();
   }

   constexpr size_t total_times = 100000;

   int pong_times = 0;
   struct pong_actor : actor {
      auto handle_message(const message_element& msg) noexcept -> void override {
         reply(msg.message_id);
         pong_times++;
      }
   };

   struct ping_actor : actor {
      actor_handle pong;
      size_t times = 0;

      auto on_init() noexcept -> void override {
         pong = spawn<pong_actor>();
         send_to(pong, 1);
         times = 1;
      }

      auto handle_message(const message_element& msg) noexcept -> void override {
         if(times++ < total_times ) {
            send_to(pong, msg.message_id + 1);
         }
         else {
            exit(exit_reason::normal);
         }
      }
   };

   SCENARIO("ping pang") {
      pong_times = 0;
      actor_system system;
      system.start(3);
      REQUIRE(system.get_num_of_actors() == 0);

      auto me = system.spawn<ping_actor>();
      REQUIRE(system.get_num_of_actors() == 2);
      REQUIRE(me.wait_for_exit() == NORMAL_EXIT);
      me.release();

      system.shutdown();
      REQUIRE(pong_times == total_times);
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
            std::cout << "async done" << std::endl;
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

      auto handle_message(const message_element& msg) noexcept -> void override {
         std::cout << "msg received" << std::endl;
      }
   };

   SCENARIO("async test") {
      actor_system system;
      system.start(1);

      auto me = system.spawn<future_actor>();
      me.send(1);
      REQUIRE(me.wait_for_exit() == NORMAL_EXIT);
      me.release();

      system.shutdown();
      REQUIRE(system.get_num_of_actors() == 0);
   }
}