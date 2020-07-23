//
// Created by Darwin Yuan on 2020/7/23.
//

#ifndef NANO_CAF_RESUMABLE_H
#define NANO_CAF_RESUMABLE_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

struct resumable {
   enum class result {
      resume_later,
      awaiting_message,
      done,
      shutdown_execution_unit
   };

   virtual auto resume() noexcept -> result = 0;

   virtual ~resumable() = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_RESUMABLE_H
