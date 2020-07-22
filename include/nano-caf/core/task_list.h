//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_TASK_LIST_H
#define NANO_CAF_TASK_LIST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/message_element.h>
#include <cstddef>

NANO_CAF_NS_BEGIN

struct task_list {
   auto pop_front() noexcept -> message_element* {
      if(head_ != nullptr) {
         auto elem = head_;
         head_ = head_->next;
         if (head_ == nullptr) tail_ = nullptr;
         total_task_size_--;
         return elem;
      }

      return nullptr;
   }

   auto push_back(message_element* ptr) noexcept -> void {
      if(tail_ != nullptr) {
         tail_->next = ptr;
      } else {
         head_ = ptr;
      }
      tail_ = ptr;
      total_task_size_++;
   }

   auto total_task_size() const noexcept -> size_t {
      return total_task_size_;
   }

   auto empty() const noexcept -> bool {
      return head_ == nullptr;
   }

   auto append_list(task_list& list) noexcept -> void{
      if(list.empty()) return;

      if(tail_ != nullptr) {
         tail_->next = list.head_;
      } else {
         head_ = list.head_;
      }

      tail_ = list.tail_;
      total_task_size_ += list.total_task_size_;

      list.head_ = nullptr;
      list.tail_ = nullptr;
      list.total_task_size_ = 0;
   }

   ~task_list() noexcept {
      while(head_ != nullptr) {
         auto ptr = head_;
         head_ = head_->next;
         delete ptr;
      }
   }

private:
   message_element* head_{};
   message_element* tail_{};
   size_t total_task_size_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_TASK_LIST_H
