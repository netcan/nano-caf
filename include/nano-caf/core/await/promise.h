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
   using obj_type = std::shared_ptr<detail::future_object<T>>;
   inline auto check_object() noexcept -> void {
      if(!object_) {
         object_ = std::make_shared<detail::future_object<T>>();
      }
   }

   auto reply(intrusive_actor_ptr& to) {
      if(to) {
         actor_handle(to).send<future_done>(object_);
      }
   }

public:
   auto get_future(on_actor_context& context) noexcept -> future<T> {
      check_object();
      return future<T>{object_, context};
   }

   auto get_promise_done_notifier() const noexcept -> std::shared_ptr<promise_done_notifier> {
      return object_;
   }

   auto has_value() const noexcept -> bool {
      return object_ && object_->present();
   }

protected:
   obj_type object_;
};

template<typename T>
struct promise : promise_base<T> {
   using super = promise_base<T>;

   auto set_value(T&& value, intrusive_actor_ptr& to) noexcept -> void override {
      super::check_object();
      if(super::object_->set_value(std::move(value))) {
         super::reply(to);
      }
   }
};

template<>
struct promise<void> : promise_base<void> {
   using super = promise_base<void>;
   auto set_value(intrusive_actor_ptr& to) noexcept -> void override {
      super::check_object();
      if(super::object_->set_value()) {
         super::reply(to);
      }
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_PROMISE_H
