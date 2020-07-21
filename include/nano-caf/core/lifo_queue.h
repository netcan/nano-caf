//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_LIFO_QUEUE_H
#define NANO_CAF_LIFO_QUEUE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/message_element.h>
#include <atomic>
#include <memory>

NANO_CAF_NS_BEGIN

enum class enq_result {
   ok,
   closed,
   blocked
};

struct lifo_queue {
   auto enqueue(message_element* msg) -> enq_result {
      auto e = head();
      auto eof = close_tag();

      while(e != eof) {
        msg->next = e;
        // if success, it's not possible e == eof.
        if(stack_.compare_exchange_strong(e, msg)) {
           return (e == block_tag()) ? enq_result::blocked : enq_result::ok;
        }
      }

      // eof for sure.
      delete msg;
      return enq_result::closed;
   }

   auto take_all() -> message_element* {
      message_element* result = head();
      while (!stack_.compare_exchange_strong(result, nullptr));
      return result;
   }

   ~lifo_queue() {
      auto result = take_all();
      while(result != nullptr) {
         auto p = result;
         result = result->next;
         delete p;
      }
   }

private:
   auto head() const volatile noexcept -> message_element* {
      return stack_.load();
   }
   auto block_tag() const noexcept -> const message_element* const {
      return reinterpret_cast<const message_element*>(__block_tag_address);
   }
   auto close_tag() const noexcept -> const message_element* const {
      return reinterpret_cast<const message_element*>(__close_tag_address) ;
   }

private:
   char __block_tag_address[0];
   std::atomic<message_element*> stack_{};
   char __close_tag_address[0];
};

NANO_CAF_NS_END

#endif //NANO_CAF_LIFO_QUEUE_H
