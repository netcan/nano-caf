//
// Created by Darwin Yuan on 2020/7/24.
//

#include <catch.hpp>
#include <nano-caf/core/sched_actor.h>
#include <nano-caf/core/message_element.h>

namespace {
   using namespace NANO_CAF_NS;

   struct my_message : message_element {
      my_message(uint32_t value, bool is_urgent = false)
         : value{value}, message_element{value,
                                         is_urgent ?
                                         message_id::category::urgent :
                                         message_id::category::normal} {}


      uint32_t value{};
   };

   SCENARIO("empty sched-actor") {
      sched_actor actor{};
      WHEN("resume an actor with empty queue, should return awaiting_message") {
         REQUIRE(actor.resume() == resumable::result::awaiting_message);
         THEN("the message queue is blocked") {
            REQUIRE(actor.blocked());
         }
      }
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

   SCENARIO("sched-actor with 2 messages") {
      my_actor actor{};
      actor.enqueue(new my_message{1});
      actor.enqueue(new my_message{2});
      WHEN("resume an actor with empty queue, should return awaiting_message") {
         REQUIRE(actor.resume() == resumable::result::awaiting_message);
         THEN("it consumed all messages") {
            REQUIRE(actor.values.size() == 2);
         }
         THEN("messages should be consumed according to their order") {
            REQUIRE(actor.values == std::vector<size_t>{1,2});
         }
         THEN("the message queue is blocked") {
            REQUIRE(actor.blocked());
         }
      }
   }

   SCENARIO("sched-actor with 5 messages") {
      my_actor actor{};
      actor.enqueue(new my_message{1});
      actor.enqueue(new my_message{2});
      actor.enqueue(new my_message{3});
      actor.enqueue(new my_message{4});
      actor.enqueue(new my_message{5});
      WHEN("resume an actor with empty queue, should return resume_later") {
         REQUIRE(actor.resume() == resumable::result::resume_later);
         THEN("it consumed 3 messages") {
            REQUIRE(actor.values.size() == 3);
         }
         THEN("messages should be consumed according to their order") {
            REQUIRE(actor.values == std::vector<size_t>{1,2,3});
         }
         THEN("the message queue is not blocked") {
            REQUIRE_FALSE(actor.blocked());
         }
         THEN("when resuming another round, should return awaiting_message") {
            actor.clear();
            REQUIRE(actor.resume() == resumable::result::awaiting_message);
            THEN("it consumed all messages") {
               REQUIRE(actor.values.size() == 2);
            }
            THEN("messages should be consumed according to their order") {
               REQUIRE(actor.values == std::vector<size_t>{4,5});
            }
            THEN("the message queue is blocked") {
               REQUIRE(actor.blocked());
            }
            WHEN("we push messages again") {
               actor.enqueue(new my_message{6});
               THEN("the message queue is not blocked") {
                  REQUIRE_FALSE(actor.blocked());
               }
            }
         }
      }
   }
}