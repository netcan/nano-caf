//
// Created by Darwin Yuan on 2020/7/21.
//

#include <catch.hpp>
#include <nano-caf/core/lifo_queue.h>

namespace {
   using namespace NANO_CAF_NS;

   struct my_message : message_element {
      my_message(int value) : value{value} {}
      int value {};
   };

   SCENARIO("empty lifo queue") {
      lifo_queue queue{};
      WHEN("enqueue a message, should return ok") {
         REQUIRE(enq_result::ok == queue.enqueue(new my_message{1}));
         WHEN("enqueue another message, should return ok") {
            REQUIRE(enq_result::ok == queue.enqueue(new my_message{2}));
            WHEN("when take_all") {
               auto msg = queue.take_all();
               THEN("the message queue should not be empty") {
                  REQUIRE(msg != nullptr);
               }
               THEN("should get only 2 message") {
                  REQUIRE(msg->next != nullptr);
                  REQUIRE(msg->next->next == nullptr);
               }
               THEN("the messages should be the ones we enqueued") {
                  REQUIRE(msg->body<my_message>().value == 2);
                  REQUIRE(msg->next->body<my_message>().value == 1);
               }
               delete msg->next;
               delete msg;
            }
            WHEN("close the queue") {
               queue.close();
               THEN("take all should return null_ptr") {
                  auto msg = queue.take_all();
                  REQUIRE(msg == nullptr);
               }
               THEN("put a new message, should return closed") {
                  REQUIRE(queue.enqueue(new my_message{3}) == enq_result::closed);
               }
            }
         }
         WHEN("when take_all") {
            auto msg = queue.take_all();
            THEN("the message queue should not be empty") {
               REQUIRE(msg != nullptr);
            }
            THEN("should get only 1 message") {
               REQUIRE(msg->next == nullptr);
            }
            THEN("the message should be the one we enqueued") {
               REQUIRE(msg->body<my_message>().value == 1);
            }
            delete msg;
         }
      }
      THEN("it's size should be the size of atomic pointer") {
         REQUIRE(sizeof(std::atomic<int*>) == sizeof(lifo_queue));
      }
   }
}