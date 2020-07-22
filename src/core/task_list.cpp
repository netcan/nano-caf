//
// Created by Darwin Yuan on 2020/7/23.
//

#include <nano-caf/core/task_list.h>
#include <nano-caf/core/message_element.h>

NANO_CAF_NS_BEGIN

auto task_list::pop_front() noexcept -> message_element* {
   if(head_ != nullptr) {
      auto elem = head_;
      head_ = head_->next;
      if (head_ == nullptr) tail_ = nullptr;
      total_task_size_--;
      elem->next = nullptr;
      return elem;
   }

   return nullptr;
}

auto task_list::push_back(message_element* ptr) noexcept -> void {
   if(tail_ != nullptr) {
      tail_->next = ptr;
   } else {
      head_ = ptr;
   }
   tail_ = ptr;
   total_task_size_++;
}

auto task_list::append_list(task_list& list) noexcept -> void{
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

task_list::~task_list() noexcept {
   while(head_ != nullptr) {
      auto ptr = head_;
      head_ = head_->next;
      delete ptr;
   }
}

NANO_CAF_NS_END