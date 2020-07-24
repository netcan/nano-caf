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

   virtual ~list_element() = default;

   template<typename T>
   auto to_value() -> T* {
      return reinterpret_cast<T*>(to_value_ptr());
   }

private:
   virtual auto to_value_ptr() -> void* = 0;
};

// we don't use double end list, because it has to
// dynamically alloc memory, which would cause more
// problems, even slower.
struct thread_safe_list {
   thread_safe_list() {
      lock_.clear();
   }

   template<typename T>
   auto pop_front() noexcept -> T* {
      spin_lock _{lock_};
      if(head_ != nullptr) {
         auto elem = head_.load(std::memory_order_relaxed);
         head_.store(elem->next, std::memory_order_relaxed);
         if (head_ == nullptr) tail_ = nullptr;
         return elem->to_value<T>();
      }

      return nullptr;
   }

   auto push_back(list_element* ptr) noexcept -> void {
      spin_lock _{lock_};
      if(tail_ != nullptr) {
         tail_->next = ptr;
      } else {
         head_ = ptr;
      }

      tail_ = ptr;
   }

   auto empty() const noexcept -> bool {
      return head_.load(std::memory_order_relaxed) == nullptr;
   }

private:
   std::atomic<list_element*> head_ {};
   list_element* tail_ {};
   std::atomic_flag lock_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_THREAD_SAFE_LIST_H
