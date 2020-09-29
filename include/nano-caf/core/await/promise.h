//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_PROMISE_H
#define NANO_CAF_PROMISE_H

#include <nano-caf/core/await/future.h>
#include <nano-caf/core/await/abstract_promise.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <memory>

NANO_CAF_NS_BEGIN

struct on_actor_context;

template<typename T>
struct promise_base : abstract_promise<T> {

protected:
   using obj_type = std::weak_ptr<detail::future_object<T>>;
   auto reply(intrusive_actor_ptr& to) {
      if(to) {
         actor_handle(to).send<future_done>(std::move(object_));
      }
   }

   auto get_future_object() noexcept -> obj_type override {
      return object_;
   }

public:
   promise_base() noexcept = default;
   explicit promise_base(obj_type object) noexcept : object_{std::move(object)} {}

   auto has_value() const noexcept -> bool {
      return object_ && object_->present();
   }

   auto get_future(on_actor_context& context) noexcept -> future<T> {
      auto f = object_.lock();
      if(f == nullptr) {
         f = std::make_shared<detail::future_object<T>>(context);
         object_ = f;
      }

      return future<T>{context, f};
   }

   auto on_fail(status_t cause, intrusive_actor_ptr& to) noexcept -> void override {
      auto f = object_.lock();
      if(f) {
         f->on_fail(cause);
         reply(to);
      }
   }

protected:
   obj_type object_;
};

template<typename T>
struct promise : promise_base<T> {
   using super = promise_base<T>;
   using super::super;

   auto set_value(T&& value, intrusive_actor_ptr& to) noexcept -> void override {
      auto object = super::object_.lock();
      if(object) {
         object->set_value(std::move(value));
         super::reply(to);
      }
   }

   auto set_value(T const& value, intrusive_actor_ptr& to) noexcept -> void override {
      auto object = super::object_.lock();
      if(object) {
         object->set_value(value);
         super::reply(to);
      }
   }
};

template<>
struct promise<void> : promise_base<void> {
   using super = promise_base<void>;
   using super::super;
   auto set_value(intrusive_actor_ptr& to) noexcept -> void override {
      auto object = super::object_.lock();
      if(object) {
         object->set_value();
         super::reply(to);
      }
   }
};

template<typename T>
auto future<T>::sink(promise<T> p, intrusive_actor_ptr& to) noexcept -> future<void> {
   if constexpr (std::is_void_v<T>) {
      return then([=]() mutable -> void { p.set_value(to); })
         .fail([=](status_t cause) mutable { p.on_fail(cause, to); });
   } else {
      return then([=](auto &&value) mutable -> void { p.set_value(std::forward<decltype(value)>(value), to); })
         .fail([=](status_t cause) mutable { p.on_fail(cause, to); });
   }
}


NANO_CAF_NS_END

#endif //NANO_CAF_PROMISE_H
