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
concept destroyable_coroutine = requires (P co) {
   { co.on_destroy() };
   { co.get_caller() } -> std::convertible_to<std::coroutine_handle<>>;
};

struct co_actor_final_awaiter {
   auto await_ready() const noexcept { return false; }

   template<destroyable_coroutine P>
   auto await_suspend(std::coroutine_handle<P> self) noexcept -> std::coroutine_handle<> {
      // before this coroutine is destroyed, it should be de-registered. so that
      // anyone who needs to know its aliveness (the timeout message, eg), is able
      // to get the precise result by querying the registry.
      self.promise().on_destroy();

      auto upper_caller = self.promise().get_caller();
      if(upper_caller) {
         return upper_caller;
      }

      // straight to the resume point, so that this coroutine could be destroyed.
      return std::noop_coroutine();
   }

   auto await_resume() const noexcept {};
};

NANO_CAF_NS_END

#endif //NANO_CAF_CO_ACTOR_FINAL_AWAITER_H
