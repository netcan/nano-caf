//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_ACTOR_INBOX_H
#define NANO_CAF_ACTOR_INBOX_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/lifo_inbox.h>
#include <nano-caf/core/actor/drr_queue.h>

NANO_CAF_NS_BEGIN

struct actor_inbox : private lifo_inbox {
   using lifo_inbox::enqueue;
   using lifo_inbox::try_block;
   using lifo_inbox::blocked;

   auto close() -> void;
   auto new_round(size_t quota, message_consumer f) noexcept -> new_round_result;
   auto empty() const noexcept -> bool {
      return urgent_queue.empty() && normal_queue.empty();
   }

private:
   auto reload() noexcept -> void;

private:
   alignas(CACHE_LINE_SIZE)
   drr_queue urgent_queue{};
   drr_queue normal_queue{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_INBOX_H
