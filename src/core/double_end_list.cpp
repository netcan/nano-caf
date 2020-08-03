//
// Created by Darwin Yuan on 2020/8/3.
//

#include <nano-caf/core/double_end_list.h>
#include <nano-caf/core/spin_lock.h>

NANO_CAF_NS_BEGIN

double_end_list::double_end_list() {
   auto node = new double_end_list_node{};
   head_ = node;
   tail_ = node;
}

double_end_list::~double_end_list() {
   double_end_list_elem* p = nullptr;
   while((p = pop_front())  != nullptr) {
      delete p;
   }
}

auto double_end_list::enqueue(double_end_list_elem* elem) -> result {
   if(elem == nullptr) return null_elem;
   auto node = elem->get_node();

   {
      spin_lock lock(tail_lock_);
      tail_.load()->next = node;
      tail_ = node;
   }

   return ok;
}

auto double_end_list::pop_front() noexcept -> double_end_list_elem* {
   double_end_list_node* first;
   double_end_list_elem* result;
   {
      spin_lock lock(head_lock_);

      first = head_.load();
      auto next = first->next.load();
      if(next == nullptr) return nullptr;

      result = next->elem.release();
      head_ = next;
   }

   // save the node for reuse
   result->put_node(first);

   return result;
}

auto double_end_list::empty() const noexcept -> bool {
   return head_.load() == tail_.load();
}

NANO_CAF_NS_END