//
// Created by Darwin Yuan on 2020/9/29.
//

#ifndef NANO_CAF_FAILURE_HANDLER_H
#define NANO_CAF_FAILURE_HANDLER_H

#include <nano-caf/util/status_t.h>
#include <functional>

NANO_CAF_NS_BEGIN

using failure_handler = std::function<auto (status_t) -> void>;

NANO_CAF_NS_END

#endif //NANO_CAF_FAILURE_HANDLER_H
