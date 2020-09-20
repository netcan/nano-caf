//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_THREAD_SAFE_LIST_H
#define NANO_CAF_THREAD_SAFE_LIST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/spin_lock.h>
#include <nano-caf/util/list_element.h>
#include <nano-caf/util/likely.h>

NANO_CAF_NS_BEGIN

// we don't use double end list, because it has to
// dynamically alloc memory, which would cause more
// problems, even slower.
struct thread_safe_list {
   thread_safe_list();

   template<typename T>
   auto dequeue() noexcept -> T* {
      auto elem = pop_front();
      if(elem == nullptr) return nullptr;
      return elem->to_value<T>();
   }

   auto reschedule(list_element* ptr) noexcept -> bool;
   auto enqueue(list_element* ptr) noexcept -> void;
   auto push_front(list_element* ptr) noexcept -> void;
   auto empty() const noexcept -> bool;
   auto pop_front() noexcept -> list_element*;

   ~thread_safe_list();

private:
   auto enqueue_(list_element* ptr) noexcept -> void;
private:
   list_element* head_ {};
   list_element* tail_ {};
   mutable std::atomic_flag lock_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_THREAD_SAFE_LIST_H
