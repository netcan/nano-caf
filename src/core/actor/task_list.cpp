//
// Created by Darwin Yuan on 2020/7/23.
//

#include <nano-caf/core/actor/task_list.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/util/likely.h>

NANO_CAF_NS_BEGIN

///////////////////////////////////////////////////////////////////////////////////
auto task_list::next(size_t& deficit) noexcept -> std::unique_ptr<message> {
   if(__unlikely(deficit == 0)) return nullptr;

   if(__likely(head_ != nullptr)) {
      auto elem = head_;
      head_ = head_->next_;
      if (head_ == nullptr) tail_ = nullptr;
      total_task_size_--;
      deficit--;
      elem->next_ = nullptr;
      return std::unique_ptr<message>(elem);
   }

   deficit = 0;
   return nullptr;
}

///////////////////////////////////////////////////////////
auto task_list::push_back(message* ptr) noexcept -> void {
   if(__likely(tail_ != nullptr)) tail_->next_ = ptr;
   else head_ = ptr;

   tail_ = ptr;
   ptr->next_ = nullptr;

   total_task_size_++;
}

///////////////////////////////////////////////////////////
auto task_list::push_front(message* ptr) noexcept -> void {
   if(__unlikely(tail_ == nullptr)) tail_ = ptr;

   ptr->next_ = head_;
   head_ = ptr;

   total_task_size_++;
}

auto task_list::take_all() noexcept -> message* {
   auto result = head_;
   reset();
   return result;
}

///////////////////////////////////////////////////////////
auto task_list::append_list(task_list& list) noexcept -> void{
   if(__unlikely(list.empty())) return;

   if(__likely(tail_ != nullptr)) {
      tail_->next_ = list.head_;
   } else {
      head_ = list.head_;
   }

   tail_ = list.tail_;
   total_task_size_ += list.total_task_size_;

   list.reset();
}

///////////////////////////////////////////////////////////
auto task_list::prepend_list(task_list& list) noexcept -> void {
   if(__unlikely(list.empty())) return;

   if(tail_ == nullptr) {
      tail_ = list.tail_;
   } else {
      list.tail_->next_ = head_;
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
auto task_list::clear() noexcept -> void {
   while(head_ != nullptr) {
      std::unique_ptr<message> ptr{head_};
      head_ = head_->next_;
   }
}

///////////////////////////////////////////////////////////
task_list::~task_list() noexcept {
   clear();
}

NANO_CAF_NS_END