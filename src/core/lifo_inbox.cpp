//
// Created by Darwin Yuan on 2020/7/21.
//

#include <nano-caf/core/lifo_inbox.h>
#include <nano-caf/core/message_element.h>

NANO_CAF_NS_BEGIN

//////////////////////////////////////////////////////////////////
auto lifo_inbox::enqueue(message_element* msg) -> enq_result {
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
auto lifo_inbox::take_all() -> message_element* {
   message_element* result = head();
   if(result == close_tag() || result == block_tag() || result == nullptr) {
      return nullptr;
   }

   while (!stack_.compare_exchange_strong(result, nullptr));
   return result;
}

//////////////////////////////////////////////////////////////////
auto lifo_inbox::try_block() -> bool {
   auto e = head();
   return stack_.compare_exchange_strong(e, block_tag());
}

//////////////////////////////////////////////////////////////////
auto lifo_inbox::close() -> void {
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
lifo_inbox::~lifo_inbox() {
   destroy(take_all());
}

//////////////////////////////////////////////////////////////////
auto lifo_inbox::destroy(message_element* result) -> void {
   while(result != nullptr) {
      auto p = result;
      result = result->next;
      delete p;
   }
}

NANO_CAF_NS_END
