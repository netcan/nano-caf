//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_EXEUTION_UNIT_H
#define NANO_CAF_EXEUTION_UNIT_H

#include <nano-caf/nano-caf-ns.h>
#include <cstddef>

NANO_CAF_NS_BEGIN

struct resumable;

struct execution_unit {
   virtual auto resume_later(resumable*) noexcept -> void = 0;
   virtual ~execution_unit() = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_EXEUTION_UNIT_H
