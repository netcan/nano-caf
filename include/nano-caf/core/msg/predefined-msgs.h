//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_PREDEFINED_MSGS_H
#define NANO_CAF_PREDEFINED_MSGS_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message_trait.h>
#include <nano-caf/core/actor/exit_reason.h>
#include <nano-caf/util/either.h>
#include <nano-caf/core/actor/intrusive_actor_ptr.h>
#include <cstdint>
#include <chrono>
#include <nano-caf/core/timer/timer_callback.h>

NANO_CAF_NS_BEGIN

CAF_def_message(exit_msg, (reason, exit_reason));
CAF_def_message(future_done);

enum class timer_unit {
   microseconds,
   milliseconds,
   seconds,
   minutes,
   hours,
};

struct duration {
   uint64_t   length;
   timer_unit unit;
};

using timer_spec = either<duration, std::chrono::system_clock::time_point>;

struct timer_id_t {
   explicit timer_id_t(uint64_t id) : id_{id} {}

   auto operator==(timer_id_t& rhs) const { return id_ == rhs.id_; }
   auto operator!=(timer_id_t& rhs) const { return id_ != rhs.id_; }
   auto operator<(timer_id_t& rhs) const  { return id_ < rhs.id_; }

private:
   uint64_t id_;
};

CAF_def_message(start_timer_msg,
    (id, timer_id_t),
    (actor, intrusive_actor_ptr),
    (spec, timer_spec),
    (issue_time_point, std::chrono::system_clock::time_point),
    (is_periodic, bool),
    (callback, std::shared_ptr<timer_callback>));

CAF_def_message(stop_timer_msg,
    (actor, intptr_t),
    (id, timer_id_t));

CAF_def_message(clear_actor_timer_msg,
    (actor, intptr_t));

CAF_def_message(timeout_msg,
    (id, timer_id_t),
    (callback, std::shared_ptr<timer_callback>));

NANO_CAF_NS_END

#endif //NANO_CAF_PREDEFINED_MSGS_H
