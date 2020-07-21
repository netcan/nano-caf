//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_LIFO_INBOX_H
#define NANO_CAF_LIFO_INBOX_H

#include <nano-caf/nano-caf-ns.h>
#include <atomic>
#include <memory>

NANO_CAF_NS_BEGIN

enum class enq_result {
   ok,
   closed,
   blocked
};

struct message_element;

struct lifo_inbox {
   auto enqueue(message_element* msg) -> enq_result;
   auto take_all() -> message_element*;
   auto try_block() -> bool;
   auto close() -> void;

   ~lifo_inbox();

private:
   auto head() const volatile noexcept -> message_element* {
      return stack_.load();
   }
   auto block_tag() const noexcept -> message_element* {
      return reinterpret_cast<message_element*>(const_cast<char*>(__block_tag_address));
   }
   auto close_tag() const noexcept ->  message_element* {
      return reinterpret_cast<message_element*>(const_cast<char*>(__close_tag_address));
   }

   auto destroy(message_element* result) -> void;

private:
   char __block_tag_address[0];
   std::atomic<message_element*> stack_{};
   char __close_tag_address[0];
};

NANO_CAF_NS_END

#endif //NANO_CAF_LIFO_INBOX_H
