//
// Created by Darwin Yuan on 2020/8/2.
//

#ifndef NANO_CAF_DRR_QUEUE_H
#define NANO_CAF_DRR_QUEUE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/task_list.h>
#include <nano-caf/core/new_round_result.h>
#include <nano-caf/core/actor/task_result.h>
#include <cstddef>
#include <functional>


NANO_CAF_NS_BEGIN

using message_consumer = std::function<auto (message&) -> task_result>;

struct drr_queue : private task_list {
   using task_list::append_list;
   using task_list::clear;

   auto new_round(size_t quota, message_consumer f) noexcept -> new_round_result;
   auto inc_deficit(size_t quota) noexcept -> void;
   auto empty() const noexcept -> bool {
      return task_list::empty();
   }

   auto deficit() noexcept -> size_t {
      auto result = deficit_;
      deficit_ = 0;
      return result;
   }

private:
   auto next() noexcept -> std::unique_ptr<message>;

   size_t deficit_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_DRR_QUEUE_H
