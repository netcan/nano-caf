//
// Created by Darwin Yuan on 2020/7/24.
//

#include <catch.hpp>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/actor.h>
#include "test_msgs.h"

namespace {
   using namespace NANO_CAF_NS;

   SCENARIO("empty sched-actor") {
      sched_actor actor{};
      WHEN("resume an actor with empty queue, should return awaiting_message") {
         REQUIRE(actor.resume());
         THEN("the message queue is blocked") {
            REQUIRE(actor.blocked());
         }
      }
   }

   struct my_actor : sched_actor {
      std::vector<int> values;
      auto user_defined_handle_msg(message& msg) noexcept -> task_result override {
         values.push_back(msg.body<test_message>()->value);
         return task_result::resume;
      }

      void clear() {
         values.clear();
      }
   };

   SCENARIO("sched-actor with 2 messages") {
      my_actor actor{};
      actor.enqueue(make_message<test_message>(1));
      actor.enqueue(make_message<test_message>(2));
      WHEN("resume an actor with empty queue, should return awaiting_message") {
         REQUIRE(actor.resume());
         THEN("it consumed all messages") {
            REQUIRE(actor.values.size() == 2);
         }
         THEN("messages should be consumed according to their order") {
            REQUIRE(actor.values == std::vector<int>{1,2});
         }
         THEN("the message queue is blocked") {
            REQUIRE(actor.blocked());
         }
      }
   }

   SCENARIO("sched-actor with 5 messages") {
      my_actor actor{};
      actor.enqueue(make_message<test_message>(1));
      actor.enqueue(make_message<test_message>(2));
      actor.enqueue(make_message<test_message>(3));
      actor.enqueue(make_message<test_message>(4));
      actor.enqueue(make_message<test_message>(5));

      WHEN("resume an actor with empty queue, should return resume_later") {
         REQUIRE_FALSE(actor.resume());
         THEN("it consumed 3 messages") {
            REQUIRE(actor.values.size() == 3);
         }
         THEN("messages should be consumed according to their order") {
            REQUIRE(actor.values == std::vector<int>{1,2,3});
         }
         THEN("the message queue is not blocked") {
            REQUIRE_FALSE(actor.blocked());
         }
         THEN("when resuming another round, should return awaiting_message") {
            actor.clear();
            REQUIRE(actor.resume());
            THEN("it consumed all messages") {
               REQUIRE(actor.values.size() == 2);
            }
            THEN("messages should be consumed according to their order") {
               REQUIRE(actor.values == std::vector<int>{4,5});
            }
            THEN("the message queue is blocked") {
               REQUIRE(actor.blocked());
            }
            WHEN("we push messages again") {
               actor.enqueue(make_message<test_message>(6));
               THEN("the message queue is not blocked") {
                  REQUIRE_FALSE(actor.blocked());
               }
               WHEN("consume again, should return awaiting message") {
                  actor.clear();
                  REQUIRE(actor.resume());
                  THEN("should consume the new enqueued message") {
                     REQUIRE(actor.values == std::vector<int>{6});
                  }
               }
            }
         }
      }
   }
}