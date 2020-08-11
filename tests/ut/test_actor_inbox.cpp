//
// Created by Darwin Yuan on 2020/7/23.
//

#include <catch.hpp>
#include <nano-caf/core/actor/actor_inbox.h>
#include <nano-caf/core/msg/make_message.h>
#include <nano-caf/util/aggregate_reflex.h>
#include "test_msgs.h"

namespace {
   using namespace NANO_CAF_NS;

   struct Foo {
      int a = 10;
      double b = 2.0;
   };

   SCENARIO("consume an empty inbox") {
      //std::cout << aggregate_fields_type<2, Foo>::type << std::endl;
      actor_inbox inbox{};
      WHEN("consume elements") {
         uint32_t times = 0;
         auto result = inbox.new_round(100, [&](const message&) noexcept  {
            times++;
            return task_result::resume; });
         THEN("should consume 0 elements") {
            REQUIRE(result == new_round_result{0});
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
         auto result = inbox.new_round(100, [&](const message&) noexcept  {
            times++;
            return task_result::resume; });
         THEN("should consume all elements") {
            REQUIRE(result == new_round_result{3});
            REQUIRE(times == 3);
         }
      }
   }

   SCENARIO("consume a non-empty inbox full of urgent") {
      actor_inbox inbox{};
      inbox.enqueue(make_message<test_message, message::urgent>(1));
      inbox.enqueue(make_message<test_message, message::urgent>(2));
      inbox.enqueue(make_message<test_message, message::urgent>(3));
      WHEN("consume elements") {
         uint32_t times = 0;
         auto result = inbox.new_round(100, [&](const message&) noexcept  {
            times++;
            return task_result::resume; });
         THEN("should consume all elements") {
            REQUIRE(*result == 3);
            REQUIRE(times == 3);
         }
      }
   }

   SCENARIO("consume a non-empty inbox mixed urgent with normal") {
      actor_inbox inbox{};
      inbox.enqueue(make_message<test_message, message::normal>(1));
      inbox.enqueue(make_message<test_message, message::urgent>(2));
      inbox.enqueue(make_message<test_message, message::urgent>(3));
      WHEN("consume 1 element") {
         auto value = 0;
         bool urgent = false;
         auto l = [&](const message& elem) noexcept  {
            value = elem.body<test_message>()->value;
            urgent = elem.is_urgent();
            return task_result::resume; };

         auto result = inbox.new_round(1, l);
         THEN("should consume the 1st urgent element") {
            REQUIRE(*result == 1);
            REQUIRE(value == 2);
            REQUIRE(urgent);
         }
         AND_WHEN("consume 1 element") {
            auto result = inbox.new_round(1, l);
            THEN("should consume the 2nd urgent element") {
               REQUIRE(*result == 1);
               REQUIRE(value == 3);
               REQUIRE(urgent);
            }
            AND_WHEN("consume 1 element") {
               auto result = inbox.new_round(1, l);
               THEN("should consume the  normal element") {
                  REQUIRE(*result == 1);
                  REQUIRE(value == 1);
                  REQUIRE_FALSE(urgent);
               }
            }
         }
      }
   }
}