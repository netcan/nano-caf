//
// Created by Darwin Yuan on 2020/8/3.
//

#ifndef NANO_CAF_DOUBLE_END_LIST_ELEM_H
#define NANO_CAF_DOUBLE_END_LIST_ELEM_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/cache_line_size.h>
#include <memory>
#include <atomic>

NANO_CAF_NS_BEGIN

struct double_end_list_elem;

struct double_end_list_node {
   std::atomic<double_end_list_node*> next{nullptr};
   double_end_list_elem* elem{nullptr};
};

struct double_end_list_elem {
   double_end_list_elem() : node(new double_end_list_node{}){
      node->elem = this;
      node->next.store(nullptr);
   }

   virtual ~double_end_list_elem() {}

   auto get_node() noexcept -> double_end_list_node* {
      return node.release();
   }

   auto put_node(double_end_list_node* mem) noexcept -> void {
      mem->next.store(nullptr);
      mem->elem = this;
      node.reset(mem);
   }

   template<typename T>
   auto to_value() -> T* {
      return reinterpret_cast<T*>(to_value_ptr());
   }

private:
   virtual auto to_value_ptr() -> void* = 0;

private:
   std::unique_ptr<double_end_list_node> node;
};

NANO_CAF_NS_END

#endif //NANO_CAF_DOUBLE_END_LIST_ELEM_H
