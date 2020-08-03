//
// Created by Darwin Yuan on 2020/8/3.
//

#ifndef NANO_CAF_LOCK_FREE_LIST_H
#define NANO_CAF_LOCK_FREE_LIST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/cache_line_size.h>
#include <nano-caf/core/double_end_list_elem.h>
#include <nano-caf/core/actor/enq_result.h>
#include <memory>

NANO_CAF_NS_BEGIN

struct lock_free_list {
   lock_free_list();
   ~lock_free_list();

   auto enqueue(double_end_list_elem* elem) -> enq_result;

   template<typename T>
   auto dequeue() noexcept -> T* {
      auto result = pop_front();
      if(result == nullptr) return nullptr;
      return result->to_value<T>();
   }

   auto empty() const noexcept -> bool;

   auto pop_front() noexcept -> double_end_list_elem*;

private:
   std::atomic<double_end_list_node*> head_;
   std::atomic<double_end_list_node*> tail_;
   std::atomic<size_t> count_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_LOCK_FREE_LIST_H
