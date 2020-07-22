//
// Created by Darwin Yuan on 2020/7/23.
//

#include <catch.hpp>
#include <nano-caf/core/task_list.h>
#include <nano-caf/core/message_element.h>

namespace {
   using namespace NANO_CAF_NS;

   struct my_message : message_element {
      my_message(uint32_t value)
         : value{value}
         , message_element{value} {}

      uint32_t value {};
   };

   TEST_CASE("an empty task list") {
      task_list list{};
      THEN("its total task size should be 0") {
         REQUIRE(list.total_task_size() == 0);
      }
      THEN("it should be an empty list") {
         REQUIRE(list.empty() == true);
      }
      WHEN("push back a new element") {
         list.push_back(new my_message{1});
         THEN("its total task size should be 1") {
            REQUIRE(list.total_task_size() == 1);
         }
         THEN("it should not be an empty list") {
            REQUIRE(list.empty() == false);
         }
         AND_WHEN("push back another element") {
            list.push_back(new my_message{2});
            THEN("its total task size should be 2") {
               REQUIRE(list.total_task_size() == 2);
            }
            THEN("it should not be an empty list") {
               REQUIRE(list.empty() == false);
            }
         }
      }
   }

   TEST_CASE("an non-empty task list") {
      task_list list{};
      list.push_back(new my_message{1});
      list.push_back(new my_message{2});
      WHEN("pop front a element, should get the first one") {
         auto ptr = list.pop_front();
         REQUIRE(ptr != nullptr);
         REQUIRE(ptr->body<my_message>().value == 1);
         delete ptr;
         AND_WHEN("pop front a element again, should get the 2nd one") {
            auto ptr = list.pop_front();
            REQUIRE(ptr != nullptr);
            REQUIRE(ptr->body<my_message>().value == 2);
            delete ptr;
            AND_WHEN("pop front a element again, should get nullptr") {
               REQUIRE(list.pop_front() == nullptr);
            }
            AND_THEN("it should not be an empty list") {
               REQUIRE(list.empty() == true);
            }
         }
      }
   }
}