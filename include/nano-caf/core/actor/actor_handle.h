//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_ACTOR_HANDLE_H
#define NANO_CAF_ACTOR_HANDLE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/actor/enq_result.h>
#include <nano-caf/core/actor/message_element.h>

NANO_CAF_NS_BEGIN

struct message_element;

struct actor_handle {
   actor_handle(intrusive_actor_ptr ptr) : ptr_{ptr} {}

   template<typename T, typename ... Args>
   auto send(const message_id& id, Args&& ... args) {
      return send_(make_message<T>(id, std::forward<Args>(args)...));
   }

private:
   auto send_(message_element*) noexcept -> enq_result;

private:
   intrusive_actor_ptr ptr_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_HANDLE_H
