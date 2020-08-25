//
// Created by Darwin Yuan on 2020/8/22.
//

#ifndef NANO_CAF_TIMER_SCHEDULER_H
#define NANO_CAF_TIMER_SCHEDULER_H

#include <nano-caf/core/actor/lifo_inbox.h>
#include <nano-caf/core/timer/timer_set.h>
#include <nano-caf/util/ipc_notifier.h>
#include <nano-caf/util/result_t.h>
#include <nano-caf/core/msg/predefined-msgs.h>
#include <thread>

NANO_CAF_NS_BEGIN

struct timer_scheduler
   : protected timer_set
{
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
   auto go_sleep() -> void;
   auto handle_msgs(message* msgs) -> void;
   auto send_msg(message* msg) -> status_t;

private:
   lifo_inbox msg_queue_{};
   std::atomic<uint64_t> timer_id_{0};
   std::atomic_bool shutdown{false};
   ipc_notifier notifier_{};
   std::thread thread_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_TIMER_SCHEDULER_H
