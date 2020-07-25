//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_THREAD_SAFE_LIST_H
#define NANO_CAF_THREAD_SAFE_LIST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/spin_lock.h>
#include <nano-caf/util/list_element.h>

NANO_CAF_NS_BEGIN

// we don't use double end list, because it has to
// dynamically alloc memory, which would cause more
// problems, even slower.
struct thread_safe_list {
   thread_safe_list() {
      lock_.clear();
   }

   template<typename T>
   auto pop_front() noexcept -> T* {
      auto elem = pop_front_();
      if(elem == nullptr) return nullptr;
      return elem->to_value<T>();
   }

   auto push_back(list_element* ptr) noexcept -> void {
      spin_lock _{lock_};

      if(tail_ != nullptr) tail_->next = ptr;
      else head_ = ptr;

      tail_ = ptr;
      ptr->next = nullptr;
   }

   auto push_front(list_element* ptr) noexcept -> void {
      spin_lock _{lock_};

      if(tail_ == nullptr) tail_ = ptr;
      ptr->next = head_;
      head_ = ptr;
   }

   auto empty() const noexcept -> bool {
      spin_lock _{lock_};
      return head_ == nullptr;
   }

   ~thread_safe_list() {
      for(auto elem = pop_front_(); elem != nullptr; elem = pop_front_()) {
         delete elem;
      }
   }

private:
   auto pop_front_() noexcept -> list_element* {
      spin_lock _{lock_};
      if(head_ != nullptr) {
         auto elem = head_;
         head_ = elem->next;
         if (head_ == nullptr) tail_ = nullptr;
         return elem;
      }

      return nullptr;
   }

private:
   list_element* head_ {};
   list_element* tail_ {};
   mutable std::atomic_flag lock_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_THREAD_SAFE_LIST_H
