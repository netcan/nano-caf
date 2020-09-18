//
// Created by Darwin Yuan on 2020/8/3.
//

#include <nano-caf/core/thread_pool/thread_safe_list.h>
#include <nano-caf/util/spin_lock.h>

NANO_CAF_NS_BEGIN

thread_safe_list::thread_safe_list() {
   lock_.clear();
}


auto thread_safe_list::enqueue(list_element* ptr) noexcept -> void {
   if(__unlikely(ptr == nullptr)) return;
   {
      spin_lock _{lock_};

      if(__likely(tail_ != nullptr)) tail_->next = ptr;
      else head_ = ptr;

      tail_ = ptr;
      ptr->next = nullptr;
   }
}

auto thread_safe_list::push_front(list_element* ptr) noexcept -> void {
   if(__unlikely(ptr == nullptr)) return;
   {
      spin_lock _{lock_};
      if(__unlikely(tail_ == nullptr)) tail_ = ptr;
      ptr->next = head_;
      head_ = ptr;
   }
}

auto thread_safe_list::empty() const noexcept -> bool {
   spin_lock _{lock_};
   return head_ == nullptr;
}

thread_safe_list::~thread_safe_list() {
   for(auto elem = pop_front(); elem != nullptr; elem = pop_front()) {
      delete elem;
   }
}

auto thread_safe_list::pop_front() noexcept -> list_element* {
   spin_lock _{lock_};
   if(__likely(head_ != nullptr)) {
      auto elem = head_;
      head_ = elem->next;
      if (head_ == nullptr) tail_ = nullptr;
      return elem;
   }

   return nullptr;
}

NANO_CAF_NS_END
