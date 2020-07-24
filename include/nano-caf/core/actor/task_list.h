//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_TASK_LIST_H
#define NANO_CAF_TASK_LIST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/message_element.h>
#include <cstddef>
#include <memory>

NANO_CAF_NS_BEGIN

enum class task_result {
   resume,
   skip,
   stop,
   stop_all,
};

struct task_list {
   auto next(size_t& deficit) noexcept -> std::unique_ptr<message_element>;
   auto push_back(message_element* ptr) noexcept -> void;
   auto push_front(message_element* ptr) noexcept -> void;
   auto append_list(task_list& list) noexcept -> void;
   auto prepend_list(task_list& list) noexcept -> void;
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
   message_element* head_{};
   message_element* tail_{};
   size_t total_task_size_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_TASK_LIST_H
