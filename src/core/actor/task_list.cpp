//
// Created by Darwin Yuan on 2020/7/23.
//

#include <nano-caf/core/actor/task_list.h>
#include <nano-caf/core/msg/message_element.h>

NANO_CAF_NS_BEGIN

///////////////////////////////////////////////////////////////////////////////////
auto task_list::next(size_t& deficit) noexcept -> std::unique_ptr<message_element> {
   if(deficit == 0) return nullptr;

   if(head_ != nullptr) {
      auto elem = head_;
      head_ = head_->next;
      if (head_ == nullptr) tail_ = nullptr;
      total_task_size_--;
      deficit--;
      elem->next = nullptr;
      return std::unique_ptr<message_element>(elem);
   }

   deficit = 0;
   return nullptr;
}

///////////////////////////////////////////////////////////
auto task_list::push_back(message_element* ptr) noexcept -> void {
   if(tail_ != nullptr) tail_->next = ptr;
   else head_ = ptr;

   tail_ = ptr;
   ptr->next = nullptr;

   total_task_size_++;
}

///////////////////////////////////////////////////////////
auto task_list::push_front(message_element* ptr) noexcept -> void {
   if(tail_ == nullptr) tail_ = ptr;

   ptr->next = head_;
   head_ = ptr;

   total_task_size_++;
}
///////////////////////////////////////////////////////////
auto task_list::append_list(task_list& list) noexcept -> void{
   if(list.empty()) return;

   if(tail_ != nullptr) {
      tail_->next = list.head_;
   } else {
      head_ = list.head_;
   }

   tail_ = list.tail_;
   total_task_size_ += list.total_task_size_;

   list.reset();
}

///////////////////////////////////////////////////////////
auto task_list::prepend_list(task_list& list) noexcept -> void {
   if(list.empty()) return;

   if(tail_ == nullptr) {
      tail_ = list.tail_;
   } else {
      list.tail_->next = head_;
   }

   head_ = list.head_;

   total_task_size_ += list.total_task_size_;

   list.reset();
}

///////////////////////////////////////////////////////////
auto task_list::reset() noexcept -> void {
   head_ = nullptr;
   tail_ = nullptr;
   total_task_size_ = 0;
}

///////////////////////////////////////////////////////////
task_list::~task_list() noexcept {
   while(head_ != nullptr) {
      auto ptr = head_;
      head_ = head_->next;
      delete ptr;
   }
}

NANO_CAF_NS_END