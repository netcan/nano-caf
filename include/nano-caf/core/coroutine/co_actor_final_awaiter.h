//
// Created by Darwin Yuan on 2020/9/17.
//

#ifndef NANO_CAF_CO_ACTOR_FINAL_AWAITER_H
#define NANO_CAF_CO_ACTOR_FINAL_AWAITER_H

#include <nano-caf/nano-caf-ns.h>
#include <coroutine>
#include <concepts>

NANO_CAF_NS_BEGIN

template<typename P>
concept awaitable_coroutine = requires (P promise) {
   { promise.on_destroy() };
   { promise.get_caller() } -> std::convertible_to<std::coroutine_handle<>>;
};

struct co_actor_final_awaiter {
   auto await_ready() const noexcept { return false; }

   template<awaitable_coroutine P>
   auto await_suspend(std::coroutine_handle<P> self) noexcept -> std::coroutine_handle<> {
      // Before this coroutine is destroyed, it must be de-registered. so that
      // anyone who needs to know its aliveness (the timeout message, eg), is able
      // to get the precise state by querying the registry.
      self.promise().on_destroy();

      auto upper_caller = self.promise().get_caller();
      // If there is a upper caller, we should transfer the execution to it symmetrically,
      // which means we have to return a coroutine_handle here, even if there isn't
      // a upper_caller.
      //
      // If there isn't a upper caller, the only option left to us is noop_coroutine,
      // which will suspend the coroutine, and resuming from a final suspend point is
      // an undefined behavior.
      //
      // Either way, this coroutine would never get a chance to be resumed, so
      // it can't be destroyed automatically any longer. Therefore we have to
      // manually destroyed it here.
      self.destroy();
      return upper_caller ? upper_caller : std::noop_coroutine();
   }

   auto await_resume() const noexcept {};
};

NANO_CAF_NS_END

#endif //NANO_CAF_CO_ACTOR_FINAL_AWAITER_H
