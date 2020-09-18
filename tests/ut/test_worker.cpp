//
// Created by Darwin Yuan on 2020/7/24.
//

#include <catch.hpp>
#include <nano-caf/core/worker.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor/make_actor.h>
#include <nano-caf/core/coordinator.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/actor/actor.h>

namespace {
   using namespace NANO_CAF_NS;

   SCENARIO("an idle worker") {
      coordinator scheduler{1};
      scheduler.shutdown();
   }

//   bool actor_deleted = false;
//   struct my_actor : actor {
//      std::vector<message_id> values;
//      auto handle_message(const message_element& msg) noexcept -> void override {
//         values.push_back(msg.message_id);
//      }
//
//      void clear() {
//         values.clear();
//      }
//
//      ~my_actor() {
//         actor_deleted = true;
//      }
//   };
//
//   SCENARIO("put a real job") {
//      actor_deleted = false;
//      {
//         actor_system system;
//         intrusive_actor_ptr actor_ctrl = make_actor<my_actor>(system);
//         auto actor = actor_ctrl->get<my_actor>();
//         coordinator scheduler{};
//         scheduler.launch(1);
//         scheduler.schedule_job(*actor);
//
//         actor->enqueue(make_message(1));
//         actor->enqueue(make_message(2));
//         actor->enqueue(make_message(3));
//         actor->enqueue(make_message(4));
//
//         std::this_thread::sleep_for(std::chrono::microseconds{100});
//
//         THEN("should be able to consume all message") {
//            REQUIRE(actor->values == std::vector<message_id>{1, 2, 3, 4});
//            WHEN("push more messages") {
//               actor->enqueue(make_message(5));
//               actor->enqueue(make_message(6));
//               scheduler.schedule_job(*actor);
//
//               std::this_thread::sleep_for(std::chrono::microseconds{100});
//               REQUIRE(actor->values == std::vector<message_id>{1,2,3,4,5,6});
//            }
//         }
//      }
//      REQUIRE(actor_deleted);
//   }
}