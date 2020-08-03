//
// Created by Darwin Yuan on 2020/8/3.
//

#include <nano-caf/core/lock_free_list.h>
#include <iostream>
#include <nano-caf/util/likely.h>

NANO_CAF_NS_BEGIN

lock_free_list::lock_free_list() {
   auto node = new double_end_list_node{};
   count_.store(0);
   head_.store(node, std::memory_order_relaxed);
   tail_.store(node, std::memory_order_relaxed);
}

////////////////////////////////////////////////////////////////////////////
lock_free_list::~lock_free_list() {
//   double_end_list_elem* p = nullptr;
//   while((p = pop_front())  != nullptr) {
//      delete p;
//   }
//
//   auto head = head_.load();
//   delete head;
}

////////////////////////////////////////////////////////////////////////////
auto lock_free_list::enqueue(double_end_list_elem* elem) -> enq_result {
   if(elem == nullptr) return enq_result::null_msg;
   auto node = elem->get_node();
   if(node == nullptr) {
      return enq_result::null_msg;
   }

   while(1) {
      auto tail = tail_.load(std::memory_order_acquire);
      auto next = tail->next.load(std::memory_order_acquire);
      if(__likely(tail == tail_.load(std::memory_order_acquire))) {
         if(next == nullptr) {
            if(tail->next.compare_exchange_strong(next, node)) {
               tail_.compare_exchange_strong(tail, node);
               count_.fetch_add(1);
               return enq_result::ok;
            }
         }
         else {
            tail_.compare_exchange_strong(tail, next);
         }
      }
   }
}

////////////////////////////////////////////////////////////////////////////
auto lock_free_list::empty() const noexcept -> bool {
   auto head = head_.load();
   return (head == tail_.load()) && (head->next.load() == nullptr);
}

////////////////////////////////////////////////////////////////////////////
auto lock_free_list::pop_front() noexcept -> double_end_list_elem* {
   while (1) {
      //std::cout << "pop_front" << std::endl;
      auto head = head_.load(std::memory_order_acquire);
      auto* tail = tail_.load(std::memory_order_acquire);
      auto next = head->next.load(std::memory_order_acquire);
      if(__likely(head == head_.load(std::memory_order_acquire))) {
         if(head == tail) {
            if(next == nullptr) {
               auto count = count_.load();
               std::cout << count << std::endl;
               return nullptr;
            } else {
               tail_.compare_exchange_strong(tail, next);
            }
         }
         else {
            if(next != nullptr) {
               auto result = next->elem;
               if(head_.compare_exchange_strong(head, next)) {
                  assert(result != nullptr);
                  result->put_node(head);
                  count_.fetch_sub(1);
                  return result;
               }
            }
         }
      }
   }
}

NANO_CAF_NS_END