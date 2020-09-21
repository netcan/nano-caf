//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_SINGLE_FUTURE_AWAITER_H
#define NANO_CAF_SINGLE_FUTURE_AWAITER_H

#include <nano-caf/core/await/promise_done_notifier.h>
#include <nano-caf/core/await/future_object.h>
#include <nano-caf/core/await/cancellable.h>
#include <nano-caf/core/await/cancellable_repository.h>
#include <memory>

NANO_CAF_NS_BEGIN

template<typename T, typename F_CALLBACK, typename F_FAIL,
   typename = std::enable_if_t<std::is_invocable_r_v<void, std::decay_t<F_CALLBACK>, const T&> &&
                               std::is_invocable_r_v<void, std::decay_t<F_FAIL>, status_t>>>
struct single_future_awaiter
   : cancellable
   , promise_done_notifier {
   using object_type = std::shared_ptr<detail::future_object<T>>;

   single_future_awaiter(cancellable_repository& repository, object_type object, F_CALLBACK&& f_callback, F_FAIL f_fail)
      : repository_{repository}
      , object_{std::move(object)}
      , callback_{std::forward<F_CALLBACK>(f_callback)}
      , on_fail_{std::forward<F_FAIL>(f_fail)} {
      if(object_) {
         if(object_->ready()) {
            callback_(object_->get_value());
            destroyed_ = true;
         }
      } else {
         f_callback(status_t::invalid_data);
         destroyed_ = true;
      }
   }

   inline auto destroyed() const noexcept -> bool { return destroyed_; }

private:
   auto destroy() {
      repository_.remove_cancellable(this);
      destroyed_ = true;
   }

   auto on_promise_done() noexcept -> void override {
      if(!destroyed_ && object_ && *object_) {
         callback_(object_->get_value());
         destroy();
      }
   }

   auto cancel(status_t cause) noexcept -> void override {
      if(!destroyed_) {
         on_fail_(cause);
         destroy();
      }
   }

private:
   cancellable_repository& repository_;
   object_type object_;
   F_CALLBACK callback_;
   F_FAIL     on_fail_;
   bool       destroyed_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_SINGLE_FUTURE_AWAITER_H
