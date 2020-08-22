//
// Created by Darwin Yuan on 2020/8/22.
//

#ifndef NANO_CAF_TIMER_SCHEDULER_H
#define NANO_CAF_TIMER_SCHEDULER_H

#include <nano-caf/core/timer/actor_timer.h>
#include <nano-caf/core/actor/lifo_inbox.h>
#include <nano-caf/core/timer/timer_set.h>
#include <nano-caf/util/ipc_notifier.h>
#include <thread>

NANO_CAF_NS_BEGIN

struct timer_scheduler
   : protected timer_set
   , actor_timer
{
   auto start() -> void;
   auto stop() -> void;

private:
   auto start_timer(intrusive_actor_ptr self,
                    const duration& duration,
                    bool periodic = false) -> result_t<uint64_t> override;
   auto stop_timer(const intrusive_actor_ptr& self, timer_id) -> void override;
   auto clear_actor_timer(const intrusive_actor_ptr& self) -> void override;

   auto schedule() -> void;
   auto go_sleep() -> void;
   auto handle_msgs(message* msgs) -> void;

private:
   lifo_inbox msg_queue_{};
   std::atomic<timer_id> timer_id_{0};
   std::atomic_bool shutdown{false};
   ipc_notifier notifier_{};
   std::thread thread_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_TIMER_SCHEDULER_H
