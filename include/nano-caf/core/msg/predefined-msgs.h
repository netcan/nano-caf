//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_PREDEFINED_MSGS_H
#define NANO_CAF_PREDEFINED_MSGS_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message_trait.h>
#include <nano-caf/core/actor/exit_reason.h>
#include <cstdint>

NANO_CAF_NS_BEGIN

CAF_def_message(exit_msg, (exit_reason) reason);
CAF_def_message(future_done);

NANO_CAF_NS_END

#endif //NANO_CAF_PREDEFINED_MSGS_H
