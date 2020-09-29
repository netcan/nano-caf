//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_FUTURE_CALLBACK_BASE_H
#define NANO_CAF_FUTURE_CALLBACK_BASE_H

#include <nano-caf/core/await/future_observer.h>
#include <nano-caf/core/await/future_object.h>

NANO_CAF_NS_BEGIN
struct on_actor_context;
NANO_CAF_NS_END

NANO_CAF_NS_BEGIN namespace detail {

template<typename R, typename F, typename A>
struct future_callback_base : future_object<R>, future_observer {
   using subject_type = std::shared_ptr<future_object<A>>;
   future_callback_base
      ( on_actor_context& context
      , subject_type subject
      , F&& f) noexcept
      : future_object<R>(context)
      , subject_{std::move(subject)}
      , f_{std::forward<F>(f)} {
      if(subject_) subject_->add_observer(this);
   }

   using super = future_object <R>;

   auto cancel(status_t cause) noexcept -> void override {
      super::cancel(cause);
      detach_subject(cause);
   }

   auto on_future_fail(status_t cause) noexcept -> void override {
      super::on_fail(cause);
      do_commit();
   }

   ~future_callback_base() {
      detach_subject(status_t::ok);
   }

protected:
   auto do_commit() noexcept -> void {
      super::commit();
      detach_subject(status_t::ok);
   }

   auto detach_subject(status_t cause) noexcept -> void {
      if(subject_) {
         subject_->deregister_observer(this, cause);
         subject_.reset();
      }
   }

protected:
   std::decay_t<F> f_;
   subject_type subject_;
};

} NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_CALLBACK_BASE_H
