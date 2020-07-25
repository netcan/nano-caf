//
// Created by Darwin Yuan on 2020/7/25.
//

#ifndef NANO_CAF_ENQ_RESULT_H
#define NANO_CAF_ENQ_RESULT_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

enum class enq_result {
   ok,
   closed,
   blocked,
   null_msg,
   null_sender
};

NANO_CAF_NS_END

#endif //NANO_CAF_ENQ_RESULT_H
