//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_PROMISE_DONE_NOTIFIER_H
#define NANO_CAF_PROMISE_DONE_NOTIFIER_H

#include <nano-caf/core/actor/intrusive_actor_ptr.h>

NANO_CAF_NS_BEGIN

struct promise_done_notifier {
   virtual auto on_promise_done() noexcept -> void = 0;
   virtual ~promise_done_notifier() noexcept = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_PROMISE_DONE_NOTIFIER_H
