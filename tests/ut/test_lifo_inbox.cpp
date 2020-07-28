//
// Created by Darwin Yuan on 2020/7/21.
//

#include <catch.hpp>
#include <nano-caf/core/actor/lifo_inbox.h>
#include <nano-caf/core/msg/message_element.h>
#include "test_msgs.h"

namespace {
   using namespace NANO_CAF_NS;

   SCENARIO("lifo inbox") {
      lifo_inbox inbox{};
      WHEN("eninbox a message, should return ok") {
         REQUIRE(enq_result::blocked == inbox.enqueue(make_message<test_message>(1)));
         WHEN("eninbox another message, should return ok") {
            REQUIRE(enq_result::ok == inbox.enqueue(make_message<test_message>(2)));
            WHEN("when take_all") {
               auto msg = inbox.take_all();
               THEN("the message inbox should not be empty") {
                  REQUIRE(msg != nullptr);
               }
               THEN("should get only 2 message") {
                  REQUIRE(msg->next != nullptr);
                  REQUIRE(msg->next->next == nullptr);
               }
               THEN("the messages should be the ones we eninboxd") {
                  REQUIRE(msg->body<test_message>()->value == 2);
                  REQUIRE(msg->next->body<test_message>()->value == 1);
               }
               delete msg->next;
               delete msg;
            }
            WHEN("check a non-closed inbox, should return false") {
               REQUIRE_FALSE(inbox.closed());
            }
            WHEN("close the inbox") {
               inbox.close();
               WHEN("check a closed inbox, should return true") {
                  REQUIRE(inbox.closed() == true);
               }
               THEN("take all should return null_ptr") {
                  REQUIRE(inbox.take_all() == nullptr);
               }
               THEN("put a new message, should return closed") {
                  REQUIRE(inbox.enqueue(make_message<test_message>(3)) == enq_result::closed);
               }
               THEN("try to block a closed queue, should return false") {
                  REQUIRE_FALSE(inbox.try_block());
               }
            }
            WHEN("try to block a non-empty inbox, should return false") {
               REQUIRE_FALSE(inbox.try_block());
            }
         }
         WHEN("when take_all") {
            auto msg = inbox.take_all();
            THEN("the message inbox should not be empty") {
               REQUIRE(msg != nullptr);
            }
            THEN("should get only 1 message") {
               REQUIRE(msg->next == nullptr);
            }
            THEN("the message should be the one we eninboxd") {
               REQUIRE(msg->body<test_message>()->value == 1);
            }
            delete msg;
         }
      }
      WHEN("ask if the inbox is blocked, should return true") {
         REQUIRE(inbox.blocked());
      }
      WHEN("try to block a non-empty inbox, should return true") {
         REQUIRE(inbox.try_block());
         THEN("if ask if the inbox is blocked, should return true") {
            REQUIRE(inbox.blocked());
         }
      }
      THEN("it's size should be the size of atomic pointer") {
         REQUIRE(sizeof(std::atomic<int*>) == sizeof(lifo_inbox));
      }
   }

   SCENARIO("take all from a lifo inbox") {
      lifo_inbox inbox{};
      REQUIRE(enq_result::blocked == inbox.enqueue(make_message<test_message>(1)));
      REQUIRE(enq_result::ok == inbox.enqueue(make_message<test_message>(2)));
      REQUIRE(enq_result::ok == inbox.enqueue(make_message<test_message>(3)));

      auto msg = inbox.take_all();
      REQUIRE(msg != nullptr);

      msg = msg->next;
      REQUIRE(msg != nullptr);

      msg = msg->next;
      REQUIRE(msg != nullptr);

      msg = msg->next;
      REQUIRE(msg == nullptr);
   }

   SCENARIO("block then push") {
      lifo_inbox inbox{};
      THEN("an empty inbox should be in block state") {
         REQUIRE(inbox.blocked());
      }
      THEN("should be able to block a empty inbox") {
         REQUIRE(inbox.try_block());
         THEN("the inbox should be blocked") {
            REQUIRE(inbox.blocked());
         }
         WHEN("should be able to push some new msg") {
            REQUIRE(enq_result::blocked == inbox.enqueue(make_message<test_message>(1)));
            THEN("the inbox should not be in block state again") {
               REQUIRE_FALSE(inbox.blocked());
               REQUIRE(enq_result::ok == inbox.enqueue(make_message<test_message>(2)));
               THEN("the inbox should not be in block state again") {
                  REQUIRE_FALSE(inbox.blocked());
               }
            }
            WHEN("take all messages") {
               auto msg = inbox.take_all();
               THEN("should be able to get the message") {
                  REQUIRE(msg != nullptr);
                  THEN("the inbox should be empty") {
                     REQUIRE(inbox.empty());
                  }
               }
            }
         }
      }
   }
}