//
// Created by Darwin Yuan on 2020/7/23.
//

#include <nano-caf/core/actor/sched_actor.h>

NANO_CAF_NS_BEGIN

constexpr size_t max_throughput = 3;

auto sched_actor::resume() noexcept  -> resumable::result {
   size_t consumed_msgs = 0;

   while (consumed_msgs < max_throughput) {
      if(actor_inbox::empty() && actor_inbox::try_block()) {
         return resumable::result::awaiting_message;
      }

      auto result = actor_inbox::new_round(max_throughput - consumed_msgs,
         [this](const message_element& msg) { return handle_message(msg); });

      if(result.stop_all) break;

      consumed_msgs += result.consumed_items;
   }

   if(actor_inbox::empty() && actor_inbox::try_block()) {
      return resumable::result::awaiting_message;
   }

   return resumable::result::resume_later;
}

NANO_CAF_NS_END