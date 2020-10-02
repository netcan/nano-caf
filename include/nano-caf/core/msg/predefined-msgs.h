//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_PREDEFINED_MSGS_H
#define NANO_CAF_PREDEFINED_MSGS_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message_trait.h>
#include <nano-caf/core/timer/timer_id_t.h>
#include <nano-caf/core/timer/timer_spec.h>
#include <nano-caf/core/timer/duration.h>
#include <nano-caf/core/actor/exit_reason.h>
#include <nano-caf/core/await/promise_done_notifier.h>
#include <nano-caf/core/actor/weak_actor_ptr.h>
#include <cstdint>
#include <memory>

NANO_CAF_NS_BEGIN

CAF_def_message(exit_msg, (reason, exit_reason));

CAF_def_message(future_done, (notifier, std::weak_ptr<promise_done_notifier>));
CAF_def_message(reply_msg, (notifier, std::unique_ptr<promise_done_notifier>));

using timeout_callback_t = std::function<auto (timer_id_t) -> void>;

CAF_def_message(start_timer_msg,
    (id, timer_id_t),
    (actor, weak_actor_ptr),
    (spec, timer_spec),
    (issue_time_point, std::chrono::steady_clock::time_point),
    (is_periodic, bool),
    (callback, std::shared_ptr<timeout_callback_t>));

CAF_def_message(stop_timer_msg,
    (actor, intptr_t),
    (id, timer_id_t));

CAF_def_message(clear_actor_timer_msg,
    (actor, intptr_t));

CAF_def_message(timeout_msg,
    (id, timer_id_t),
    (callback, std::shared_ptr<timeout_callback_t>));

NANO_CAF_NS_END

#endif //NANO_CAF_PREDEFINED_MSGS_H
