//
// Created by Darwin Yuan on 2020/7/28.
//

#include <catch.hpp>
#include <nano-caf/core/actor/behavior.h>
#include <nano-caf/core/msg/make_message.h>
#include <iostream>
#include "test_msgs.h"

namespace {
   using namespace NANO_CAF_NS;

   behavior get_behavior() {
      return {
         [](shared_buf_msg_atom, std::shared_ptr<big_msg> ptr) {
            std::cout << ":" << ptr->b << std::endl;
         },
         [](my_message_atom, const int &amount, double currency) {
            std::cout << amount << ", " << currency << std::endl;
         },

         [](exit_msg_atom, exit_reason) {}
      };
   }

   SCENARIO("behavior") {
      WHEN("pass a my_message") {
         auto behavior = get_behavior();
         std::unique_ptr<message> msg{make_message<my_message>(10, 2.4)};
         REQUIRE(msg != nullptr);
         REQUIRE(behavior.ptr_ != nullptr);
         REQUIRE(behavior.ptr_->handle_msg(*msg)== task_result::resume);
      }
      WHEN("pass a shared_buf_msg") {
         auto behavior = get_behavior();
         std::unique_ptr<message> msg{make_message<shared_buf_msg>(std::shared_ptr<big_msg>(new big_msg{20, (float)1.4, 2.5}))};
         REQUIRE(msg != nullptr);
         REQUIRE(behavior.ptr_ != nullptr);
         REQUIRE(behavior.ptr_->handle_msg(*msg)== task_result::resume);
      }

      WHEN("pass a test_message") {
         auto behavior = get_behavior();
         std::unique_ptr<message> msg{make_message<test_message>(100)};
         REQUIRE(msg != nullptr);
         REQUIRE(behavior.ptr_ != nullptr);
         THEN("should return skip") {
            REQUIRE(behavior.ptr_->handle_msg(*msg)== task_result::skip);
         }
      }
   }
}