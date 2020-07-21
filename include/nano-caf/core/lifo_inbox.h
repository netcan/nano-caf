//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_LIFO_INBOX_H
#define NANO_CAF_LIFO_INBOX_H

#include <nano-caf/nano-caf-ns.h>
#include <atomic>

NANO_CAF_NS_BEGIN

enum class enq_result {
   ok,
   closed,
   blocked
};

struct message_element;

struct lifo_inbox {
   auto enqueue(message_element* msg) noexcept -> enq_result;
   auto take_all() noexcept -> message_element*;
   auto try_block() noexcept -> bool;
   auto close() noexcept -> void;

   auto closed() const noexcept -> bool {
      return head() == close_tag();
   }

   auto blocked() const noexcept -> bool {
      return head() == block_tag();
   }

   ~lifo_inbox() noexcept;

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

   auto destroy(message_element* result) noexcept -> void;

private:
   char __block_tag_address[0];
   std::atomic<message_element*> stack_{};
   char __close_tag_address[0];
};

NANO_CAF_NS_END

#endif //NANO_CAF_LIFO_INBOX_H
