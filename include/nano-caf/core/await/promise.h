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
   auto reply(intrusive_actor_ptr&& to) {
      if(to) {
         actor_handle(to).send<future_done>(std::move(object_));
      }
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

   auto on_fail(status_t cause, intrusive_actor_ptr&& to) noexcept -> void override {
      if(!to) return;
      auto f = object_.lock();
      if(f) {
         f->on_fail(cause);
         reply(std::move(to));
      }
   }

protected:
   obj_type object_;
};

namespace detail {
   template <typename T>
   auto reply_to(weak_actor_ptr&& to, std::weak_ptr<detail::future_object<T>>&& object) {
      auto to_actor = to.lock();
      if(to_actor) {
         actor_handle(to_actor).send<future_done>(std::move(object));
      }
   }
}

template<typename T>
struct promise : promise_base<T> {
   using super = promise_base<T>;
   using super::super;

   auto set_value(T&& value, intrusive_actor_ptr&& to) noexcept -> void override {
      if(!to) return;
      auto object = super::object_.lock();
      if(object) {
         object->set_value(std::move(value));
         super::reply(std::move(to));
      }
   }

   auto set_value(T const& value, intrusive_actor_ptr&& to) noexcept -> void override {
      if(!to) return;
      auto object = super::object_.lock();
      if(object) {
         object->set_value(value);
         super::reply(std::move(to));
      }
   }

   virtual auto set_future(future<T>&& future, weak_actor_ptr&& to) noexcept -> void override {
      future.then([obj = super::object_, to = std::move(to)](auto &&value) mutable -> void {
         auto object = obj.lock();
         if(object) {
            object->set_value(value);
            detail::reply_to(std::move(to), std::move(obj));
         }
      })
      .fail([obj = super::object_, to = std::move(to)](status_t cause) mutable {
         auto object = obj.lock();
         if(object) {
            object->on_fail(cause);
            detail::reply_to(std::move(to), std::move(obj));
         }
      });
   }
};

template<>
struct promise<void> : promise_base<void> {
   using super = promise_base<void>;
   using super::super;
   auto set_value(intrusive_actor_ptr&& to) noexcept -> void override {
      if(!to) return;
      auto object = super::object_.lock();
      if(object) {
         object->set_value();
         super::reply(std::move(to));
      }
   }

   virtual auto set_future(future<void>&& future, weak_actor_ptr&& to) noexcept -> void override {
      future.then([obj = super::object_, to = std::move(to)]() mutable -> void {
            auto object = obj.lock();
            if(object) {
               object->set_value();
               detail::reply_to(std::move(to), std::move(obj));
            }
         })
         .fail([obj = super::object_, to = std::move(to)](status_t cause) mutable {
            auto object = obj.lock();
            if(object) {
               object->on_fail(cause);
               detail::reply_to(std::move(to), std::move(obj));
            }
         });
   }
};

template<typename T>
auto future<T>::sink(promise<T> p, weak_actor_ptr& to) noexcept -> future<void> {
   if constexpr (std::is_void_v<T>) {
      return then([=]() mutable -> void { p.set_value(to.lock()); })
         .fail([=](status_t cause) mutable { p.on_fail(cause, to.lock()); });
   } else {
      return then([=](auto &&value) mutable -> void { p.set_value(std::forward<decltype(value)>(value), to.lock()); })
         .fail([=](status_t cause) mutable { p.on_fail(cause, to.lock()); });
   }
}


NANO_CAF_NS_END

#endif //NANO_CAF_PROMISE_H
