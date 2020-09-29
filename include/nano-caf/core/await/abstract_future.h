//
// Created by Darwin Yuan on 2020/9/29.
//

#ifndef NANO_CAF_ABSTRACT_FUTURE_H
#define NANO_CAF_ABSTRACT_FUTURE_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

struct abstract_future {
   virtual auto on_registered() noexcept -> void = 0;
   virtual ~abstract_future() noexcept = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_ABSTRACT_FUTURE_H
