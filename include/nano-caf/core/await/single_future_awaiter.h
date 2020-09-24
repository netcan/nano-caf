//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_SINGLE_FUTURE_AWAITER_H
#define NANO_CAF_SINGLE_FUTURE_AWAITER_H

#include <nano-caf/core/await/future_done_notifier.h>
#include <nano-caf/core/await/future_object.h>
#include <nano-caf/core/await/abstract_future_awaiter.h>
#include <memory>

NANO_CAF_NS_BEGIN

template<typename T, typename F_CALLBACK, typename F_FAIL,
   typename = std::enable_if_t<std::is_invocable_r_v<void, std::decay_t<F_CALLBACK>, const T&> &&
                               std::is_invocable_r_v<void, std::decay_t<F_FAIL>, status_t>>>
struct single_future_awaiter
   : abstract_future_awaiter {
   using object_type = std::shared_ptr<detail::future_object<T>>;

   single_future_awaiter(on_actor_context& context,
                         object_type object,
                         F_CALLBACK&& f_callback,
                         F_FAIL&& f_fail)
      : abstract_future_awaiter{context}
      , object_{std::move(object)}
      , callback_{std::forward<F_CALLBACK>(f_callback)}
      , on_fail_{std::forward<F_FAIL>(f_fail)} {
      if(object_) {
         f_callback(status_t::invalid_data);
         destroyed_ = true;
      } else if(object_->ready()) {
         callback_(object_->get_value());
         destroyed_ = true;
      }
   }

private:
   auto on_future_done() noexcept -> void override {
      if(!destroyed_ && object_) {
         callback_(object_->get_value());
         destroy();
      }
   }


   auto on_fail(status_t cause) noexcept -> void override {
      on_fail_(cause);
   }

private:
   object_type object_;
   F_CALLBACK callback_;
   F_FAIL     on_fail_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_SINGLE_FUTURE_AWAITER_H
