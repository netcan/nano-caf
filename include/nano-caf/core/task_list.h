//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_TASK_LIST_H
#define NANO_CAF_TASK_LIST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/message_element.h>
#include <cstddef>

NANO_CAF_NS_BEGIN

struct task_list {
   auto pop_front() noexcept -> message_element*;
   auto push_back(message_element* ptr) noexcept -> void;
   auto append_list(task_list& list) noexcept -> void;
   ~task_list() noexcept;

   auto total_task_size() const noexcept -> size_t {
      return total_task_size_;
   }

   auto empty() const noexcept -> bool {
      return head_ == nullptr;
   }

private:
   message_element* head_{};
   message_element* tail_{};
   size_t total_task_size_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_TASK_LIST_H
