//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_ACTOR_INBOX_H
#define NANO_CAF_ACTOR_INBOX_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/message_element.h>
#include <nano-caf/core/lifo_inbox.h>
#include "drr_cached_queue.h"

NANO_CAF_NS_BEGIN

struct actor_inbox : private lifo_inbox {
   using lifo_inbox::enqueue;
   auto new_round(size_t quota, message_consumer f) noexcept -> new_round_result;

private:
   auto reload() noexcept -> void;

private:
   drr_cached_queue urgent_queue{};
   drr_cached_queue normal_queue{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_INBOX_H
