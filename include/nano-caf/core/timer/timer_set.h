//
// Created by Darwin Yuan on 2020/8/22.
//

#ifndef NANO_CAF_TIMER_SET_H
#define NANO_CAF_TIMER_SET_H

#include <nano-caf/core/actor/lifo_inbox.h>
#include <nano-caf/util/cv_notifier.h>
#include <nano-caf/util/status_t.h>
#include <nano-caf/core/msg/predefined-msgs.h>
#include <map>
#include <nano-caf/core/actor/shutdown_notifier.h>

NANO_CAF_NS_BEGIN

struct timer_set {
   auto add_timer(std::unique_ptr<message> msg) -> status_t;
   auto remove_timer(intptr_t, timer_id_t) -> void;
   auto clear_actor_timers(intptr_t) -> void;
   auto on_timeout(const shutdown_notifier& shutdown) -> void;
   auto reset() -> void;

protected:
   using time_point = std::chrono::system_clock::time_point;
   using timers = std::multimap<time_point, std::unique_ptr<message>>;

   timers timers_{};
   std::multimap<intptr_t, timers::iterator> actor_indexer_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_TIMER_SET_H
