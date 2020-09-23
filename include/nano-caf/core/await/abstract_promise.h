//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_ABSTRACT_PROMISE_H
#define NANO_CAF_ABSTRACT_PROMISE_H

#include <nano-caf/core/actor/intrusive_actor_ptr.h>

NANO_CAF_NS_BEGIN

template<typename T>
struct abstract_promise {
   virtual auto set_value(T&& value, intrusive_actor_ptr&) noexcept -> void = 0;
   virtual ~abstract_promise() = default;
};

template<>
struct abstract_promise<void> {
   virtual auto set_value(intrusive_actor_ptr&) noexcept -> void = 0;
   virtual ~abstract_promise() = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_ABSTRACT_PROMISE_H
