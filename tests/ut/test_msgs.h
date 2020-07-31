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

CAF_def_message(my_message, (int) amount, (double) currency);
CAF_def_message(test_message, (int) value);
CAF_def_message(shared_buf_msg, (std::shared_ptr<big_msg>) obj);

NANO_CAF_NS_END

#endif //NANO_CAF_TEST_MSGS_H
