//
// Created by Darwin Yuan on 2020/9/23.
//

#ifndef NANO_CAF_ABSTRACT_FUTURE_AWAITER_H
#define NANO_CAF_ABSTRACT_FUTURE_AWAITER_H

#include <nano-caf/util/status_t.h>
#include <nano-caf/core/await/cancellable.h>
#include <nano-caf/core/actor/on_actor_context.h>

NANO_CAF_NS_BEGIN

struct abstract_future_awaiter: cancellable {

   explicit abstract_future_awaiter(on_actor_context& context)
      : context_{context} {}

   auto cancel(status_t cause) noexcept -> void {
      if(destroyed_) return;
      on_fail(cause);
      destroy();
   }

   inline auto destroyed() const noexcept -> bool { return destroyed_; }

protected:
   auto destroy() -> void {
      context_.remove_cancellable(this);
      if(timer_id_) {
         context_.stop_timer(*timer_id_);
         timer_id_ = std::nullopt;
      }
      destroyed_ = true;
   }

private:
   auto start_timer(uint64_t duration, std::weak_ptr<cancellable> ptr) noexcept -> status_t override {
      auto result = start_timer_(duration, ptr);
      if(result != status_t::ok) {
         cancel(result);
      }
      return result;
   }

   auto start_timer_(uint64_t duration, std::weak_ptr<cancellable> ptr) noexcept -> status_t {
      auto cb = std::make_shared<timeout_callback_t>([obj = ptr](auto){
         auto cancellable = obj.lock();
         if(cancellable) {
            cancellable->timeout();
         }
      });
      if(cb == nullptr) {
         return status_t::out_of_mem;
      }

      auto result = context_.start_timer(duration, false, cb);
      if(result.is_ok()) {
         timer_id_ = *result;
      }

      return result.failure();
   }

   auto timeout() noexcept -> void override {
      timer_id_ = std::nullopt;
      cancel(status_t::timeout);
   }

private:
   virtual auto on_fail(status_t status) noexcept -> void = 0;

protected:
   on_actor_context& context_;
   bool       destroyed_{false};

private:
   std::optional<timer_id_t> timer_id_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_ABSTRACT_FUTURE_AWAITER_H
