//
// Created by Darwin Yuan on 2020/8/2.
//

#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/actor/actor.h>
#include <iostream>
#include <nanobench.h>
#include "../ut/test_msgs.h"

using namespace NANO_CAF_NS;

struct future_actor : actor {
   const int value = 10;
   unsigned long final_result = 0;

   auto add(int a, int b) {
      unsigned long result = 0;
      for(int i = 0; i < 100000000; i++) {
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

////         auto result1 = with(future1)([this](unsigned long r1) {
////            //std::cout << "async future1 done = " << r1 << std::endl;
////         });
////
////         if(!result1) {
////            exit(exit_reason::unhandled_exception);
////         }
////
////         auto result2 = with(future2)([this](unsigned long r2) {
////            //std::cout << "async future2 done = " << r2 << std::endl;
////         });
////
////         if(!result2) {
////            exit(exit_reason::unhandled_exception);
////         }
//
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

   auto handle_message(message& msg) noexcept -> task_result override {
      return task_result::resume;
   }
};

int main() {
   actor_system system;
   system.start(1);
   ankerl::nanobench::Bench().run("future calc", [&] {
      auto me = system.spawn<future_actor>();
      me.send<test_message>(1);
      me.wait_for_exit();
      me.release();
   });

   system.shutdown();
   std::cout << "shutdown" << std::endl;

   return 0;
}