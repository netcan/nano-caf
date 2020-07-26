//
// Created by Darwin Yuan on 2020/7/26.
//

#ifndef NANO_CAF_WAIT_RESULT_H
#define NANO_CAF_WAIT_RESULT_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/exit_reason.h>
#include <cstdint>

NANO_CAF_NS_BEGIN

struct wait_result {
   enum result {
      exited,
      invalid_handle,
      timeout
   };
   result result;
   exit_reason reason;

   auto tie() const {
      return std::tie(result, reason);
   }
   auto operator==(const wait_result& rhs) const -> bool {
      return tie() == rhs.tie();
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_WAIT_RESULT_H
