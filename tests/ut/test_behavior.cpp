//
// Created by Darwin Yuan on 2020/7/28.
//

#include <catch.hpp>
#include <nano-caf/core/actor/behavior.h>
#include <nano-caf/core/msg/message_element.h>
#include <iostream>
#include "test_msgs.h"

namespace {
   using namespace NANO_CAF_NS;

   behavior behaviors{
      [](my_message_atom, int&, double) {},
      [](const my_message&) {},
      [](exit_msg_atom, exit_reason) {}
   };

   SCENARIO("id") {
      std::cout << from_msg_type_to_id<my_message>::msg_id << std::endl;
   }
}