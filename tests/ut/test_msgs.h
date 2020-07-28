//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_TEST_MSGS_H
#define NANO_CAF_TEST_MSGS_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message_trait.h>
#include <nano-caf/core/msg/predefined-msgs.h>
#include <cstdint>

NANO_CAF_NS_BEGIN

struct big_msg {
   int a;
   float b;
   double c;
};

#include <nano-caf/core/msg/message_trait_interp.h>
#include "test_msg_def.h"

#include <nano-caf/core/msg/message_field_interp.h>
#include "test_msg_def.h"

#include <nano-caf/core/msg/message_interp_end.h>

NANO_CAF_NS_END

#endif //NANO_CAF_TEST_MSGS_H
