//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_LIFO_INBOX_H
#define NANO_CAF_LIFO_INBOX_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/enq_result.h>
#include <atomic>

NANO_CAF_NS_BEGIN

struct message;

struct lifo_inbox {
   lifo_inbox();
   auto enqueue(message* msg) noexcept -> enq_result;
   auto take_all() noexcept -> message*;
   auto try_block() noexcept -> bool;
   auto close() noexcept -> void;

   auto closed() const noexcept -> bool {
      return head() == close_tag();
   }

   auto blocked() const noexcept -> bool {
      return head() == block_tag();
   }

   auto empty() const noexcept -> bool {
      return head() == nullptr;
   }

   ~lifo_inbox() noexcept;

private:
   auto head() const volatile noexcept -> message* {
      return stack_.load();
   }
   auto block_tag() const noexcept -> message* {
      return reinterpret_cast<message*>(const_cast<char*>(__block_tag_address));
   }
   auto close_tag() const noexcept ->  message* {
      return reinterpret_cast<message*>(const_cast<char*>(__close_tag_address));
   }

   auto destroy(message* result) noexcept -> void;

private:
   char __block_tag_address[0];
   std::atomic<message*> stack_{};
   char __close_tag_address[0];
};

NANO_CAF_NS_END

#endif //NANO_CAF_LIFO_INBOX_H
