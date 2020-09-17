//
// Created by Darwin Yuan on 2020/9/17.
//

#ifndef NANO_CAF_ACTOR_PROMISE_H
#define NANO_CAF_ACTOR_PROMISE_H

#include <nano-caf/core/coroutine/co_actor_context.h>
#include <coroutine>

NANO_CAF_NS_BEGIN

template<typename P>
struct actor_promise {
   using handle_type = std::coroutine_handle<P>;

   template<typename ACTOR>
   requires std::is_base_of_v<co_actor_context, std::decay_t<ACTOR>>
   actor_promise(ACTOR& actor) noexcept
   : actor_{static_cast<co_actor_context&>(const_cast<ACTOR&>(actor))} {
      on_create();
   }

   template<typename ACTOR>
   requires std::is_base_of_v<co_actor_context, std::decay_t<std::remove_pointer_t<ACTOR>>>
   actor_promise(ACTOR* actor) noexcept
      : actor_{*static_cast<co_actor_context*>(const_cast<ACTOR*>(actor))} {
      on_create();
   }

   auto on_create() noexcept -> void {
      // once this coroutine is created successfully, it should be registered
      // to the actor, so that its lifetime could be maintained automatically.
      actor_.coroutines_.on_create(handle_type::from_promise(*reinterpret_cast<P*>(this)));
   }

   auto on_destroy() noexcept -> void {
      actor_.coroutines_.on_destroy(handle_type::from_promise(*reinterpret_cast<P*>(this)));
   }

   auto get_actor() const noexcept -> decltype(auto) { return actor_; }
   auto get_self_handle() const noexcept -> intrusive_actor_ptr {
      return actor_.self_handle();
   }

   auto save_caller(std::coroutine_handle<> caller) noexcept { caller_ = caller; }
   auto get_caller() const noexcept { return caller_; }

private:
   co_actor_context& actor_;
   std::coroutine_handle<> caller_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_PROMISE_H
