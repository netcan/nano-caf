//
// Created by Darwin Yuan on 2020/7/23.
//

#include <catch.hpp>
#include <nano-caf/core/actor_inbox.h>
#include <nano-caf/core/message_element.h>

namespace {
   using namespace NANO_CAF_NS;

   struct my_message : message_element {
      my_message(uint32_t value)
         : value{value}, message_element{value} {}

      uint32_t value{};
   };

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

   SCENARIO("consume a non-empty inbox") {
      actor_inbox inbox{};
      inbox.enqueue(new my_message{1});
      inbox.enqueue(new my_message{2});
      inbox.enqueue(new my_message{3});
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
}