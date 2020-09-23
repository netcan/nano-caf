//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_TASK_LIST_H
#define NANO_CAF_TASK_LIST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message.h>
#include <cstddef>
#include <memory>

NANO_CAF_NS_BEGIN

struct task_list {
   auto next(size_t& deficit) noexcept -> std::unique_ptr<message>;
   auto push_back(message* ptr) noexcept -> void;
   auto push_front(message* ptr) noexcept -> void;
   auto take_all() noexcept -> message*;
   auto append_list(task_list& list) noexcept -> void;
   auto prepend_list(task_list& list) noexcept -> void;
   auto clear() noexcept -> void;
   ~task_list() noexcept;

   auto total_task_size() const noexcept -> size_t {
      return total_task_size_;
   }

   auto empty() const noexcept -> bool {
      return head_ == nullptr;
   }

private:
   auto reset() noexcept -> void;

private:
   message* head_{};
   message* tail_{};
   size_t total_task_size_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_TASK_LIST_H
