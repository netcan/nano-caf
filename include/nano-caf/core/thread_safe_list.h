//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_THREAD_SAFE_LIST_H
#define NANO_CAF_THREAD_SAFE_LIST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/spin_lock.h>

NANO_CAF_NS_BEGIN

struct list_element {
   list_element* next;
};

// we don't use double end list, because it has to
// dynamically alloc memory, which would cause more
// problems, even slower.
struct thread_safe_list {
   thread_safe_list() {
      lock.clear();
   }

   template<typename T>
   auto pop_front() -> T* {
      spin_lock lock(lock);
      if(head_ != nullptr) {
         auto elem = head_;
         head_ = head_->next;
         if (head_ == nullptr) tail_ = nullptr;
         return reinterpret_cast<T*>(elem);
      }

      return nullptr;
   }

   auto push_back(list_element* ptr) -> void {
      spin_lock lock(lock);
      if(tail_ != nullptr) {
         tail_->next = ptr;
      } else {
         head_ = ptr;
      }

      tail_ = ptr;
   }

private:
   list_element* head_ {};
   list_element* tail_ {};
   std::atomic_flag lock;
};

NANO_CAF_NS_END

#endif //NANO_CAF_THREAD_SAFE_LIST_H
