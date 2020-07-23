//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_DRR_CACHED_QUEUE_H
#define NANO_CAF_DRR_CACHED_QUEUE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/message_element.h>
#include <cstddef>
#include <nano-caf/core/task_list.h>

NANO_CAF_NS_BEGIN

struct new_round_result {
   size_t consumed_items;
   bool stop_all;
};

struct drr_list : private task_list {
   using task_list::append_list;
   using consumer = auto (*)(const message_element&) -> task_result;
   auto new_round(size_t quota, consumer f) noexcept -> new_round_result;

private:
   auto next() noexcept -> std::unique_ptr<message_element> {
      return task_list::next(deficit_);
   }

private:
   task_list cache_{};
   size_t deficit_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_DRR_CACHED_QUEUE_H
