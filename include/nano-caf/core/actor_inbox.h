//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_ACTOR_INBOX_H
#define NANO_CAF_ACTOR_INBOX_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/message_element.h>
#include <nano-caf/core/lifo_inbox.h>

NANO_CAF_NS_BEGIN

struct actor_inbox : private lifo_inbox {
   using lifo_inbox::enqueue;
   auto next() -> message_element*;

private:
   auto reload() noexcept -> message_element*;

private:
   // only 1 thread access this, no lock required.
   message_element* head{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_INBOX_H
