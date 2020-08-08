//
// Created by Darwin Yuan on 2020/8/4.
//

#include <nano-caf/core/actor/task_stack.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/util/likely.h>

NANO_CAF_NS_BEGIN

///////////////////////////////////////////////////////////////////////////////////
auto task_stack::pop(size_t& deficit) noexcept -> std::unique_ptr<message> {
   if(__unlikely(deficit == 0)) return nullptr;

   if(__likely(top_ != nullptr)) {
      auto elem = top_;
      top_ = top_->next_;
      total_task_size_--;
      deficit--;
      elem->next_ = nullptr;
      return std::unique_ptr<message>(elem);
   }

   deficit = 0;
   return nullptr;
}

///////////////////////////////////////////////////////////
auto task_stack::push(message* ptr) noexcept -> bool {
   if(__unlikely(ptr == nullptr)) return false;

   ptr->next_ = top_;
   top_ = ptr;

   total_task_size_++;

   return true;
}

///////////////////////////////////////////////////////////
task_stack::~task_stack() noexcept {
   while(top_ != nullptr) {
      auto ptr = top_;
      top_ = top_->next_;
      delete ptr;
   }
}

NANO_CAF_NS_END