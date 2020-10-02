//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_FUTURE_OBJECT_BASE_H
#define NANO_CAF_FUTURE_OBJECT_BASE_H

#include <nano-caf/core/await/abstract_future.h>
#include <nano-caf/core/actor/on_actor_context.h>
#include <nano-caf/core/await/detail/future_observer.h>
#include <nano-caf/core/await/failure_handler.h>
#include <nano-caf/util/status_t.h>
#include <memory>
#include <deque>

NANO_CAF_NS_BEGIN namespace detail {

template<typename T> struct future_callback_trait {
   using type = std::function<auto(T) -> void>;
};

template<> struct future_callback_trait<void> {
   using type = std::function<auto() -> void>;
};

struct future_object_base : abstract_future, promise_done_notifier {
   using observer_type = future_observer*;

   explicit future_object_base(on_actor_context& context) noexcept
      : registered_{0}, ready_{0}, context_{context} {}

   auto set_fail_handler(failure_handler&& handler) noexcept -> void;
   auto add_observer(observer_type observer) noexcept -> void;
   auto commit() noexcept -> void override;

   virtual auto cancel(status_t cause) noexcept -> void { do_cancel(cause); }

   auto deregister_observer(future_observer* observer, status_t cause) noexcept -> void;
   auto on_fail(status_t cause) noexcept -> void;

   auto ready() const noexcept -> bool { return ready_; }

   auto destroy() noexcept -> void;

   auto on_registered() noexcept -> void override { registered_ = true; }
   auto get_context() const noexcept -> on_actor_context* { return &context_; }

   virtual ~future_object_base() noexcept = default;

protected:
   auto cancel_observers(status_t cause) noexcept -> void;
   auto notify_observers() noexcept -> void;

private:
   auto do_cancel(status_t cause) noexcept -> void;
   auto cancel_observer(observer_type &observer, status_t cause) noexcept -> void;
   auto notify_observer_(observer_type &observer) noexcept -> void;

private:
   on_actor_context& context_;
   std::deque<observer_type> observers_;
   status_t failure_{};
   failure_handler f_on_fail_;

protected:
   bool present_{false};
   uint8_t registered_:1;
   uint8_t ready_:1;
};

} NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_OBJECT_BASE_H
