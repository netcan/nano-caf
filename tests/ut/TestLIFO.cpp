//
// Created by Darwin Yuan on 2020/7/21.
//

#include <catch.hpp>
#include <nano-caf/core/lifo_queue.h>

namespace {
   using namespace NANO_CAF_NS;

   SCENARIO("empty lifo queue") {
      lifo_queue queue{};
      WHEN("enqueue a message, should return ok") {
         REQUIRE(enq_result::ok == queue.enqueue(new message_element{}));
      }
   }
}