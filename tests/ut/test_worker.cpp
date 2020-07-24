//
// Created by Darwin Yuan on 2020/7/24.
//

#include <catch.hpp>
#include <nano-caf/core/worker.h>
#include <nano-caf/core/actor/message_element.h>

namespace {
   using namespace NANO_CAF_NS;

   struct my_message : message_element {
      my_message(uint32_t value)
         : value{value}, message_element{value} {}

      uint32_t value{};
   };

   SCENARIO("an idle worker") {
      worker worker;
      worker.launch();
      worker.stop();
      worker.wait_done();
   }
}