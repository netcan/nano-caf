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
   auto next() noexcept -> std::unique_ptr<message_element>;

private:
   auto reload() noexcept -> message_element*;

private:
   drr_list normal_list{};
   drr_list urgent_list{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_INBOX_H
