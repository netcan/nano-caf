//
// Created by Darwin Yuan on 2020/7/28.
//

#include <catch.hpp>
#include <nano-caf/core/actor/behavior.h>
#include <nano-caf/core/msg/message_element.h>
#include "test_msgs.h"

namespace {
   using namespace NANO_CAF_NS;

   behavior behaviors{
      [](my_message_atom, int, double) {},
      [](const my_message&) {}
   };
}