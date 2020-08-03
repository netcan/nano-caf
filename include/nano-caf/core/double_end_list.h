//
// Created by Darwin Yuan on 2020/8/3.
//

#ifndef NANO_CAF_DOUBLE_END_LIST_H
#define NANO_CAF_DOUBLE_END_LIST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/cache_line_size.h>
#include <nano-caf/core/thread_safe_list.h>
#include <nano-caf/core/double_end_list_elem.h>
#include <nano-caf/core/actor/enq_result.h>
#include <memory>

NANO_CAF_NS_BEGIN

// should try:
// Michael & Scott algorithm
struct
alignas(CACHE_LINE_SIZE)
double_end_list {

   double_end_list();
   ~double_end_list();

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
   alignas(CACHE_LINE_SIZE) char __align_boundary_0[0];
   std::atomic<double_end_list_node*> head_{nullptr};
   std::atomic_flag head_lock_{false};

   alignas(CACHE_LINE_SIZE) char __align_boundary_1[0];
   std::atomic<double_end_list_node*> tail_{nullptr};
   std::atomic_flag tail_lock_{false};

   alignas(CACHE_LINE_SIZE) char __align_boundary_2[0];
};

#ifdef USE_DOUBLE_END_LIST
using list_element_t = double_end_list_elem;
using job_list_t = double_end_list;
#else
using list_element_t = list_element;
using job_list_t = thread_safe_list;
#endif

NANO_CAF_NS_END

#endif //NANO_CAF_DOUBLE_END_LIST_H
