//
// Created by Darwin Yuan on 2020/8/4.
//

#ifndef NANO_CAF_TASK_STACK_H
#define NANO_CAF_TASK_STACK_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message.h>
#include <cstddef>
#include <memory>

NANO_CAF_NS_BEGIN

struct task_stack {
   auto pop(size_t& deficit) noexcept -> std::unique_ptr<message>;
   auto push(message* ptr) noexcept -> bool;
   ~task_stack() noexcept;

   auto total_task_size() const noexcept -> size_t {
      return total_task_size_;
   }

   auto empty() const noexcept -> bool {
      return top_ == nullptr;
   }

private:
   message* top_{nullptr};
   size_t total_task_size_{0};
};

NANO_CAF_NS_END

#endif //NANO_CAF_TASK_STACK_H
