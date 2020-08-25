//
// Created by Darwin Yuan on 2020/8/22.
//

#ifndef NANO_CAF_TIMER_SET_H
#define NANO_CAF_TIMER_SET_H

#include <nano-caf/core/timer/actor_timer.h>
#include <nano-caf/core/actor/lifo_inbox.h>
#include <nano-caf/util/ipc_notifier.h>
#include <nano-caf/util/status_t.h>
#include <nano-caf/core/msg/predefined-msgs.h>
#include <map>

NANO_CAF_NS_BEGIN

struct timer_set {
   auto add_timer(std::unique_ptr<message> msg) -> status_t;
   auto remove_timer(intptr_t, timer_id_t) -> void;
   auto clear_actor_timers(intptr_t) -> void;
   auto on_timeout(std::atomic_bool& shutdown) -> void;
   auto reset() -> void;

protected:
   using time_point = std::chrono::system_clock::time_point;
   using timers = std::multimap<time_point, std::unique_ptr<message>>;

   timers timers_{};
   std::multimap<intptr_t, timers::iterator> actor_indexer_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_TIMER_SET_H
