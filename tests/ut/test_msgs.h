//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_TEST_MSGS_H
#define NANO_CAF_TEST_MSGS_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message_trait.h>
#include <nano-caf/core/msg/predefined-msgs.h>
#include <cstdint>

struct big_msg {
   int a;
   float b;
   double c;
};

CAF_def_message(my_message,
   (amount,   int),
   (currency, double));

CAF_def_message(test_message,
   (value,   int));

CAF_def_message(shared_buf_msg,
   (obj,     std::shared_ptr<big_msg>));

#endif //NANO_CAF_TEST_MSGS_H
