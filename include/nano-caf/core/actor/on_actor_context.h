//
// Created by Darwin Yuan on 2020/9/23.
//

#ifndef NANO_CAF_ON_ACTOR_CONTEXT_H
#define NANO_CAF_ON_ACTOR_CONTEXT_H

#include <nano-caf/core/actor_context.h>
#include <nano-caf/core/await/cancellable_repository.h>

NANO_CAF_NS_BEGIN

struct actor_timer_context {
   virtual auto start_timer(timer_spec const& spec, bool periodic, std::shared_ptr<timeout_callback_t> callback) -> result_t<timer_id_t> = 0;
   virtual auto stop_timer(timer_id_t timer_id) -> void = 0;
   virtual ~actor_timer_context() = default;
};

struct on_actor_context
   : actor_timer_context
   , cancellable_repository {

};

NANO_CAF_NS_END

#endif //NANO_CAF_ON_ACTOR_CONTEXT_H
