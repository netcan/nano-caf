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
struct promise : abstract_promise<T> {
private:
   using obj_type = std::shared_ptr<detail::future_object<T>>;
   inline auto check_object() noexcept -> void {
      if(!object_) {
         object_ = std::make_shared<detail::future_object<T>>();
      }
   }

public:
   auto get_future(on_actor_context& context) noexcept -> future<T> {
      check_object();
      return future<T>{object_, context};
   }

   auto set_value(T&& value, intrusive_actor_ptr& to) noexcept -> void override {
      check_object();
      if(object_->set_value(std::move(value))) {
         if(to) {
            actor_handle(to).send<future_done>(std::move(object_));
         }
      }
   }

   auto get_promise_done_notifier() const noexcept -> std::shared_ptr<promise_done_notifier> {
      return object_;
   }

   auto has_value() const noexcept -> bool {
      return object_ && object_->present();
   }

private:
   obj_type object_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_PROMISE_H
