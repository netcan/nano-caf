//
// Created by Darwin Yuan on 2020/8/22.
//

#ifndef NANO_CAF_ACTOR_TIMER_H
#define NANO_CAF_ACTOR_TIMER_H

#include <nano-caf/core/actor/lifo_inbox.h>
#include <nano-caf/core/timer/timer_set.h>
#include <nano-caf/util/cv_notifier.h>
#include <nano-caf/util/result_t.h>
#include <nano-caf/core/msg/predefined-msgs.h>
#include <nano-caf/core/actor/shutdown_notifier.h>
#include <thread>

NANO_CAF_NS_BEGIN

struct actor_timer {
   auto start() -> void;
   auto stop() -> void;

   auto start_timer( intrusive_actor_ptr self,
                     timer_spec const& spec,
                     bool periodic,
                     std::shared_ptr<timeout_callback_t> callback) -> result_t<timer_id_t>;

   auto stop_timer(const intrusive_actor_ptr& self, timer_id_t) -> status_t;
   auto clear_actor_timer(const intrusive_actor_ptr& self) -> status_t;

private:
   auto schedule() -> void;
   auto go_sleep() -> status_t;
   auto send_msg(message* msg) -> status_t;
   auto try_go_sleep() -> status_t;
   auto process(message* msgs) -> status_t;

private:
   std::thread thread_;
   timer_set timers_{};

   lifo_inbox msg_queue_{};
   cv_notifier cv_{};

   shutdown_notifier shutdown_{};

   std::atomic<uint64_t> timer_id_{0};
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_TIMER_H
