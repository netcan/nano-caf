//
// Created by Darwin Yuan on 2020/7/21.
//

#include <nano-caf/core/lifo_inbox.h>
#include <nano-caf/core/message_element.h>

NANO_CAF_NS_BEGIN

//////////////////////////////////////////////////////////////////
auto lifo_inbox::enqueue(message_element* msg) noexcept -> enq_result {
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

//////////////////////////////////////////////////////////////////
auto lifo_inbox::take_all() noexcept -> message_element* {
   message_element* result = head();
   if(result == close_tag() || result == block_tag() || result == nullptr) {
      return nullptr;
   }

   while (!stack_.compare_exchange_strong(result, nullptr));
   return result;
}

//////////////////////////////////////////////////////////////////
auto lifo_inbox::try_block() noexcept -> bool {
   message_element* e = nullptr;
   return stack_.compare_exchange_strong(e, block_tag());
}

//////////////////////////////////////////////////////////////////
auto lifo_inbox::close() noexcept -> void {
   auto eof = close_tag();
   auto e = head();
   if(e == eof) return;

   while (!stack_.compare_exchange_strong(e, eof));

   if(e == nullptr || e == block_tag() || e == close_tag()) {
      return;
   }

   destroy(e);
}

//////////////////////////////////////////////////////////////////
lifo_inbox::~lifo_inbox() noexcept {
   destroy(take_all());
}

//////////////////////////////////////////////////////////////////
auto lifo_inbox::destroy(message_element* result) noexcept -> void {
   while(result != nullptr) {
      auto p = result;
      result = result->next;
      delete p;
   }
}

NANO_CAF_NS_END
