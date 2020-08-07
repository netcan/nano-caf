//
// Created by Darwin Yuan on 2020/8/3.
//

#include <nano-caf/core/lock_free_list.h>
#include <iostream>
#include <nano-caf/util/likely.h>

NANO_CAF_NS_BEGIN

lock_free_list::lock_free_list() {
   auto node = new detail::lock_free_list_node{};
   head_.store({node, 0}, std::memory_order_relaxed);
   tail_.store({node, 0}, std::memory_order_relaxed);
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
auto lock_free_list::enqueue(lock_free_list_elem* elem) -> enq_result {
   if(elem == nullptr) return enq_result::null_msg;
   auto node = elem->get_node();
   if(node == nullptr) {
      return enq_result::null_msg;
   }

   while(1) {
      auto tail = tail_.load(std::memory_order_relaxed);
      auto next = tail.p_->next.load(std::memory_order_relaxed); // the order is promised by dependency
      // make sure the consistent of tail & next by second read.
      if(__likely(tail == tail_.load(std::memory_order_seq_cst))) {
         if(next.p_ == nullptr) {
            if(tail.p_->next.compare_exchange_strong(next, {node, next.count_+1},std::memory_order_relaxed)) {
               tail_.compare_exchange_strong(tail, {node, tail.count_+1},std::memory_order_release);
               return enq_result::ok;
            }
         }
         else {
            tail_.compare_exchange_strong(tail, {next.p_, tail.count_ + 1},std::memory_order_relaxed);
         }
      }
   }
}

//////////////////////////////////////////////////////////////////////////////
auto lock_free_list::empty() const noexcept -> bool {
   auto head = head_.load(std::memory_order_relaxed);
   return (head.p_ == tail_.load(std::memory_order_relaxed).p_) &&
      (head.p_->next.load(std::memory_order_relaxed).p_ == nullptr);
}

////////////////////////////////////////////////////////////////////////////
auto lock_free_list::pop_front() noexcept -> lock_free_list_elem* {
   while (1) {
      auto head = head_.load(std::memory_order_relaxed);
      auto next = head.p_->next.load(std::memory_order_relaxed);
      auto tail = tail_.load(std::memory_order_relaxed);
      if(__likely(head == head_.load(std::memory_order_seq_cst))) { // head, next & tail are consistent.
         if(__unlikely(head.p_ == tail.p_)) {
            if(next.p_ == nullptr) {
               return nullptr;
            } else {
               tail_.compare_exchange_weak(tail, {next.p_, tail.count_ + 1},std::memory_order_relaxed);
            }
         }
         else {
            if(__likely(next.p_ != nullptr)) {
               auto result = next.p_->elem;
               if(head_.compare_exchange_strong(head, {next.p_, head.count_ + 1},std::memory_order_relaxed)) {
                  result->put_node(head.p_);
                  return result;
               }
            }
         }
      }
   }
}

NANO_CAF_NS_END