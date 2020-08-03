//
// Created by Darwin Yuan on 2020/8/3.
//

#ifndef NANO_CAF_DOUBLE_END_LIST_H
#define NANO_CAF_DOUBLE_END_LIST_H

#include <nano-caf/nano-caf-ns.h>
#include <memory>
#include "cache_line_size.h"

NANO_CAF_NS_BEGIN

struct double_end_list_elem;


struct double_end_list_node {
   std::atomic<double_end_list_node*> next{};
   double_end_list_elem* elem;
};

struct double_end_list_elem {
   double_end_list_elem() : node(new double_end_list_node{}){
      node->elem = this;
   }

   virtual ~double_end_list_elem() {}

   auto get_node() noexcept -> double_end_list_node* {
      return node.release();
   }

   auto put_node(double_end_list_node* mem) noexcept -> void {
      mem->next = nullptr;
      node.reset(mem);
   }
private:
   std::unique_ptr<double_end_list_node> node;
};

struct
alignas(CACHE_LINE_SIZE)
double_end_list {
   enum result : uint8_t {
      ok,
      null_elem,
      alloc_fail
   };

   double_end_list();
   ~double_end_list();

   auto enqueue(double_end_list_elem* elem) -> result;

   template<typename T>
   auto dequeue() noexcept -> std::unique_ptr<T> {
      return std::unique_ptr<T>(reinterpret_cast<T*>(pop_front()));
   }

   auto pop_front() noexcept -> double_end_list_elem*;

   auto empty() const noexcept -> bool;

private:
   alignas(CACHE_LINE_SIZE) char __align_boundary_0[0];
   std::atomic<double_end_list_node*> head_{nullptr};
   std::atomic_flag head_lock_{false};

   alignas(CACHE_LINE_SIZE) char __align_boundary_1[0];
   std::atomic<double_end_list_node*> tail_{nullptr};
   std::atomic_flag tail_lock_{false};

   alignas(CACHE_LINE_SIZE) char __align_boundary_2[0];
};

NANO_CAF_NS_END

#endif //NANO_CAF_DOUBLE_END_LIST_H
