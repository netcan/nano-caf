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

NANO_CAF_NS_BEGIN

CAF_def_message(exit_msg, (reason, exit_reason));

struct done_notifier {
   virtual auto on_done() -> void = 0;
   virtual ~done_notifier() = default;
};

CAF_def_message(future_done, (notifier, std::unique_ptr<done_notifier>));
CAF_def_message(reply_msg, (notifier, std::unique_ptr<done_notifier>));

using duration = uint64_t ;

using timer_spec = either<duration, std::chrono::steady_clock::time_point>;

struct timer_id_t {
   explicit timer_id_t(uint64_t id) : id_{id} {}

   //auto operator=(timer_id_t const&) noexcept -> timer_id_t& = default;

   auto operator==(timer_id_t& rhs) const { return id_ == rhs.id_; }
   auto operator!=(timer_id_t& rhs) const { return id_ != rhs.id_; }
   auto operator<(timer_id_t& rhs) const  { return id_ < rhs.id_; }

private:
   uint64_t id_;
};

using timeout_callback_t = std::function<auto () -> void>;

CAF_def_message(start_timer_msg,
    (id, timer_id_t),
    (actor, intrusive_actor_ptr),
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
