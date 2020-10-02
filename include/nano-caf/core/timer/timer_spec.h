//
// Created by Darwin Yuan on 2020/10/2.
//

#ifndef NANO_CAF_TIMER_SPEC_H
#define NANO_CAF_TIMER_SPEC_H

#include <nano-caf/core/timer/duration.h>
#include <nano-caf/util/either.h>
#include <chrono>

NANO_CAF_NS_BEGIN

using timer_spec = either<duration, std::chrono::steady_clock::time_point>;

NANO_CAF_NS_END

#endif //NANO_CAF_TIMER_SPEC_H
