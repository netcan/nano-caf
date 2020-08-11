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

struct lock_free_list_elem;

namespace detail {
   struct lock_free_list_node;

   struct lock_free_node_handle {
      lock_free_list_node* p_{};
      size_t count_{};

      auto operator==(const lock_free_node_handle& rhs) const -> bool {
         return p_ == rhs.p_ && count_ == rhs.count_;
      }
   };

   struct lock_free_list_node {
      std::atomic<lock_free_node_handle> next{};
      lock_free_list_elem* elem{nullptr};
   };
}


struct lock_free_list_elem {
   lock_free_list_elem()
      : node(new detail::lock_free_list_node{}){
      node->elem = this;
   }

   virtual ~lock_free_list_elem() {}

   template<typename T>
   auto to_value() -> T* {
      return reinterpret_cast<T*>(to_value_ptr());
   }

private:
   auto get_node() noexcept -> detail::lock_free_list_node* {
      return node.release();
   }

   auto put_node(detail::lock_free_list_node* mem) noexcept -> void {
      if(mem == nullptr) return;
      mem->elem = this;
      mem->next.store({.p_ = nullptr, .count_ = mem->next.load(std::memory_order_relaxed).count_});
      node.reset(mem);
   }

   friend struct lock_free_list;

private:
   virtual auto to_value_ptr() -> void* = 0;

private:
   std::unique_ptr<detail::lock_free_list_node> node;
};

struct lock_free_list {
   lock_free_list();
   ~lock_free_list();

   auto enqueue(lock_free_list_elem* elem) -> enq_result;

   template<typename T>
   auto dequeue() noexcept -> T* {
      auto result = pop_front();
      if(result == nullptr) return nullptr;
      return result->to_value<T>();
   }

   auto empty() const noexcept -> bool;

   auto pop_front() noexcept -> lock_free_list_elem*;

private:
   alignas(CACHE_LINE_SIZE)
   std::atomic<detail::lock_free_node_handle> head_{};
   alignas(CACHE_LINE_SIZE)
   std::atomic<detail::lock_free_node_handle> tail_{};
   [[maybe_unused]] alignas(CACHE_LINE_SIZE) char __cache_line_alignment[0];
};

NANO_CAF_NS_END

#endif //NANO_CAF_LOCK_FREE_LIST_H
