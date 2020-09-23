//
// Created by Darwin Yuan on 2020/9/23.
//

#ifndef NANO_CAF_ON_ACTOR_CONTEXT_H
#define NANO_CAF_ON_ACTOR_CONTEXT_H

#include <nano-caf/core/actor_context.h>
#include <nano-caf/core/await/cancellable_repository.h>

NANO_CAF_NS_BEGIN

struct actor_timer_context {
   auto start_timer(timer_spec const& spec, bool periodic, std::shared_ptr<timeout_callback_t> callback) -> result_t<timer_id_t> {
      auto result = get_system_actor_context().start_timer(self_handle(), spec, periodic, std::move(callback));
      if(result.is_ok()) {
         on_timer_created();
      }
      return result;
   }

   inline auto stop_timer(timer_id_t timer_id) -> void {
      get_system_actor_context().stop_timer(self_handle(), timer_id);
   }

   virtual ~actor_timer_context() = default;
private:
   virtual auto on_timer_created() -> void = 0;
   virtual auto get_system_actor_context() -> system_actor_context& = 0;
   virtual auto self_handle() const noexcept -> intrusive_actor_ptr = 0;
};

struct on_actor_context
   : actor_timer_context
   , cancellable_repository {

};

NANO_CAF_NS_END

#endif //NANO_CAF_ON_ACTOR_CONTEXT_H
