//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_DRR_CACHED_QUEUE_H
#define NANO_CAF_DRR_CACHED_QUEUE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/message_element.h>
#include <nano-caf/core/task_list.h>
#include <nano-caf/core/new_round_result.h>
#include <cstddef>

NANO_CAF_NS_BEGIN

using message_consumer = auto (*)(const message_element&) noexcept -> task_result;

struct drr_cached_queue : private task_list {
   using task_list::append_list;
   auto new_round(size_t quota, message_consumer f) noexcept -> new_round_result;
   auto inc_deficit(size_t quota) noexcept -> void;

private:
   auto next() noexcept -> std::unique_ptr<message_element>;

private:
   task_list cache_{};
   size_t deficit_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_DRR_CACHED_QUEUE_H
