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
         // symmetric transfer to other co-routine, which means this co-routine
         // can't be destroyed automatically (we don't do it in task destructor either),
         // so we must manually destroy it here.
         self.destroy();
         return upper_caller;
      }

      // Since we have to return a coroutine_handle here, and
      // resuming from final suspend point is an undefined behavior,
      // which means we can't return the handle of this coroutine.
      // The only option left to us is noop_coroutine, which will suspend
      // the coroutine, so this coroutine won't be destroyed automatically.
      // the only thing we can do is destroying it here, and return
      // the execution to the resumer.
      //self.destroy();
      return std::noop_coroutine();
   }

   auto await_resume() const noexcept {};
};

NANO_CAF_NS_END

#endif //NANO_CAF_CO_ACTOR_FINAL_AWAITER_H
