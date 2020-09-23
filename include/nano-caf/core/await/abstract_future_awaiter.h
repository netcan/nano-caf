//
// Created by Darwin Yuan on 2020/9/23.
//

#ifndef NANO_CAF_ABSTRACT_FUTURE_AWAITER_H
#define NANO_CAF_ABSTRACT_FUTURE_AWAITER_H

#include <nano-caf/util/status_t.h>
#include <nano-caf/core/await/awaiter.h>
#include <nano-caf/core/actor/on_actor_context.h>

NANO_CAF_NS_BEGIN

struct abstract_future_awaiter: awaiter {
   explicit abstract_future_awaiter(on_actor_context& context)
      : context_{context} {}

   auto cancel(status_t cause) noexcept -> void;
   inline auto destroyed() const noexcept -> bool { return destroyed_; }

private:
   auto await(uint64_t duration, std::weak_ptr<awaiter> ptr) noexcept -> status_t override;
   auto start_timer_(uint64_t duration, std::weak_ptr<awaiter> ptr) noexcept -> status_t;
   auto timeout() noexcept -> void override;

private:
   virtual auto on_fail(status_t status) noexcept -> void = 0;

protected:
   auto destroy() -> void;

protected:
   on_actor_context& context_;
   bool       destroyed_{false};

private:
   std::optional<timer_id_t> timer_id_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_ABSTRACT_FUTURE_AWAITER_H
