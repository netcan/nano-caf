//
// Created by Darwin Yuan on 2020/7/23.
//

#include <catch.hpp>
#include <nano-caf/core/actor/actor_inbox.h>
#include <nano-caf/core/actor/message_element.h>

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
      inbox.enqueue(make_message(1));
      inbox.enqueue(make_message(2));
      inbox.enqueue(make_message(3));
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
      inbox.enqueue(make_message({1, true}));
      inbox.enqueue(make_message({2, true}));
      inbox.enqueue(make_message({3, true}));
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
      inbox.enqueue(make_message({1, false}));
      inbox.enqueue(make_message({2, true}));
      inbox.enqueue(make_message({3, true}));
      WHEN("consume 1 element") {
         message_id value = 0;
         auto result = inbox.new_round(1, [&](const message_element& elem) noexcept  {
            value = elem.message_id;
            return task_result::resume; });
         THEN("should consume the 1st urgent element") {
            REQUIRE(result.consumed_items == 1);
            REQUIRE(value == message_id{2, true});
         }
         AND_WHEN("consume 1 element") {
            auto result = inbox.new_round(1, [&](const message_element& elem) noexcept  {
               value = elem.message_id;
               return task_result::resume; });
            THEN("should consume the 2nd urgent element") {
               REQUIRE(result.consumed_items == 1);
               REQUIRE(value == message_id{3, true});
            }
            AND_WHEN("consume 1 element") {
               auto result = inbox.new_round(1, [&](const message_element& elem) noexcept  {
                  value = elem.message_id;
                  return task_result::resume; });
               THEN("should consume the  normal element") {
                  REQUIRE(result.consumed_items == 1);
                  REQUIRE(value == message_id{1});
               }
            }
         }
      }
   }
}