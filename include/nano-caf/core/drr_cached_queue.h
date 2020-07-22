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

struct drr_list {
   void append_list(task_list& list) {
      list_.append_list(list);
   }

private:
   task_list list_{};
   task_list cache_{};
   size_t deficit_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_DRR_CACHED_QUEUE_H
