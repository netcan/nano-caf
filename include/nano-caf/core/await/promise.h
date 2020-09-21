//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_PROMISE_H
#define NANO_CAF_PROMISE_H

#include <nano-caf/core/await/future.h>
#include <nano-caf/core/await/abstract_promise.h>
#include <memory>
#include <nano-caf/core/actor/actor_handle.h>

NANO_CAF_NS_BEGIN

struct cancellable_repository;

template<typename T>
struct promise : abstract_promise<T> {
private:
   using obj_type = std::shared_ptr<detail::future_object<T>>;
   inline auto check_object() noexcept -> void {
      if(!object_) {
         object_ = std::make_shared<detail::future_object<T>>();
      }
   }

public:
   auto get_future(cancellable_repository& repository) noexcept -> future<T> {
      check_object();
      return future<T>{object_, repository};
   }

   auto set_value(T&& value, intrusive_actor_ptr& to) noexcept -> void override {
      check_object();
      if(object_->set_value(std::move(value))) {
         if(to) {
            actor_handle(to).send<future_done>(object_);
         }
      }
   }

   auto get_promise_done_notifier() const noexcept -> std::shared_ptr<promise_done_notifier> {
      return object_;
   }

private:
   obj_type object_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_PROMISE_H
