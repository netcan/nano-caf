//
// Created by Darwin Yuan on 2020/9/17.
//

#ifndef NANO_CAF_CO_TASK_H
#define NANO_CAF_CO_TASK_H

#include <nano-caf/core/coroutine/co_actor_context.h>
#include <coroutine>

NANO_CAF_NS_BEGIN

template<typename P>
struct co_task {
   using handle_type = std::coroutine_handle<P>;

   co_task() noexcept = default;
   co_task(co_actor_context& actor, handle_type self) noexcept
   : actor_{&actor}, self_{self} {}

   auto is_valid() const noexcept -> bool {
      return self_ && actor_ && actor_->coroutine_alive(self_);
   }

   auto promise() const -> decltype(auto) {
      return self_.promise();
   }
private:
   co_actor_context* actor_{};
   handle_type self_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_CO_TASK_H
