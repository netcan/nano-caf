//
// Created by Darwin Yuan on 2020/9/23.
//

#ifndef NANO_CAF_FUTURE_OBSERVER_H
#define NANO_CAF_FUTURE_OBSERVER_H

#include <nano-caf/util/status_t.h>

NANO_CAF_NS_BEGIN

struct future_observer {
   virtual auto on_future_ready() noexcept -> void = 0;
   virtual auto on_future_fail(status_t cause) noexcept -> void = 0;
   virtual ~future_observer() noexcept = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_OBSERVER_H
