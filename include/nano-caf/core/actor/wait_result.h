//
// Created by Darwin Yuan on 2020/7/26.
//

#ifndef NANO_CAF_WAIT_RESULT_H
#define NANO_CAF_WAIT_RESULT_H

#include <nano-caf/nano-caf-ns.h>
#include <cstdint>
#include "exit_reason.h"

NANO_CAF_NS_BEGIN

struct wait_result {
   enum result {
      exited,
      invalid_handle,
      timeout
   };
   result result;
   exit_reason reason;
};

NANO_CAF_NS_END

#endif //NANO_CAF_WAIT_RESULT_H
