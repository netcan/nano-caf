//
// Created by Darwin Yuan on 2020/7/24.
//

#include <catch.hpp>
#include <nano-caf/core/actor/message_element.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>

namespace {
   using namespace NANO_CAF_NS;

   struct my_message : message_element {
      my_message(uint32_t value)
         : value{value}, message_element{value} {}

      uint32_t value{};
   };

   SCENARIO("a do-nothing actor system") {
      actor_system system;
      system.start(5);
      system.stop();
   }

   struct my_actor : sched_actor {
      std::vector<size_t> values;
      auto handle_message(const message_element& msg) noexcept -> task_result override {
         values.push_back(msg.body<my_message>().value);
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

      actor.send(new my_message{1});

      std::this_thread::sleep_for(std::chrono::microseconds{100});

      system.stop();
   }
}