//
// Created by Darwin Yuan on 2020/7/23.
//

#include <catch.hpp>
#include <nano-caf/core/actor/actor_inbox.h>
#include <nano-caf/core/msg/message_element.h>
#include "test_msgs.h"

namespace {
   using namespace NANO_CAF_NS;

   SCENARIO("consume an empty inbox") {
      actor_inbox inbox{};
      WHEN("consume elements") {
         uint32_t times = 0;
         auto result = inbox.new_round(100, [&](const message_element& elem) noexcept  {
            times++;
            return task_result::resume; });
         THEN("should consume 0 elements") {
            REQUIRE(result == new_round_result{.consumed_items = 0, .stop_all = false});
            REQUIRE(times == 0);
         }
      }
   }

   SCENARIO("consume a non-empty inbox full of normal msg") {
      actor_inbox inbox{};
      inbox.enqueue(make_message<test_message>(1));
      inbox.enqueue(make_message<test_message>(2));
      inbox.enqueue(make_message<test_message>(3));
      WHEN("consume elements") {
         uint32_t times = 0;
         auto result = inbox.new_round(100, [&](const message_element& elem) noexcept  {
            times++;
            return task_result::resume; });
         THEN("should consume all elements") {
            REQUIRE(result == new_round_result{.consumed_items = 3, .stop_all = false});
            REQUIRE(times == 3);
         }
      }
   }

   SCENARIO("consume a non-empty inbox full of urgent") {
      actor_inbox inbox{};
      inbox.enqueue(make_message<test_message, message_id::urgent>(1));
      inbox.enqueue(make_message<test_message, message_id::urgent>(2));
      inbox.enqueue(make_message<test_message, message_id::urgent>(3));
      WHEN("consume elements") {
         uint32_t times = 0;
         auto result = inbox.new_round(100, [&](const message_element& elem) noexcept  {
            times++;
            return task_result::resume; });
         THEN("should consume all elements") {
            REQUIRE(result.consumed_items == 3);
            REQUIRE(times == 3);
         }
      }
   }

   SCENARIO("consume a non-empty inbox mixed urgent with normal") {
      actor_inbox inbox{};
      inbox.enqueue(make_message<test_message, message_id::normal>(1));
      inbox.enqueue(make_message<test_message, message_id::urgent>(2));
      inbox.enqueue(make_message<test_message, message_id::urgent>(3));
      WHEN("consume 1 element") {
         auto value = 0;
         bool urgent = false;
         auto l = [&](const message_element& elem) noexcept  {
            value = elem.body<test_message>()->value;
            urgent = elem.is_urgent();
            return task_result::resume; };

         auto result = inbox.new_round(1, l);
         THEN("should consume the 1st urgent element") {
            REQUIRE(result.consumed_items == 1);
            REQUIRE(value == 2);
            REQUIRE(urgent);
         }
         AND_WHEN("consume 1 element") {
            auto result = inbox.new_round(1, l);
            THEN("should consume the 2nd urgent element") {
               REQUIRE(result.consumed_items == 1);
               REQUIRE(value == 3);
               REQUIRE(urgent);
            }
            AND_WHEN("consume 1 element") {
               auto result = inbox.new_round(1, l);
               THEN("should consume the  normal element") {
                  REQUIRE(result.consumed_items == 1);
                  REQUIRE(value == 1);
                  REQUIRE_FALSE(urgent);
               }
            }
         }
      }
   }
}