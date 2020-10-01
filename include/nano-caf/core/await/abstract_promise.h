//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_ABSTRACT_PROMISE_H
#define NANO_CAF_ABSTRACT_PROMISE_H

#include <nano-caf/core/actor/intrusive_actor_ptr.h>
#include <nano-caf/core/await/detail/future_object.h>

NANO_CAF_NS_BEGIN

template<typename T>
struct abstract_promise_base {
   virtual auto get_future_object() noexcept -> std::weak_ptr<detail::future_object<T>> { return {}; }
   virtual auto on_fail(status_t, intrusive_actor_ptr&& to) noexcept -> void {}
   virtual ~abstract_promise_base() = default;
};

template<typename T>
struct abstract_promise : abstract_promise_base<T> {
   virtual auto set_value(T&& value, intrusive_actor_ptr&&) noexcept -> void = 0;
   virtual auto set_value(T const& value, intrusive_actor_ptr&&) noexcept -> void = 0;
};

template<>
struct abstract_promise<void> : abstract_promise_base<void> {
   virtual auto set_value(intrusive_actor_ptr&&) noexcept -> void = 0;
   virtual ~abstract_promise() = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_ABSTRACT_PROMISE_H
