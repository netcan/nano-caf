//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_ACTOR_HANDLE_H
#define NANO_CAF_ACTOR_HANDLE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/actor/enq_result.h>
#include <nano-caf/core/actor/message_element.h>
#include <nano-caf/core/actor/wait_result.h>

NANO_CAF_NS_BEGIN

struct message_element;

struct actor_handle {
   actor_handle(intrusive_actor_ptr ptr = nullptr) : ptr_{ptr} {}

   template<typename T, typename ... Args>
   auto send(message_id const& id, Args&& ... args) noexcept {
      return send_(make_message<T>(id, std::forward<Args>(args)...));
   }

   auto send(message_id const& id) noexcept {
      return send_(make_message(id));
   }

   template<typename T, typename ... Args>
   auto send(intrusive_actor_ptr const& from, message_id const& id, Args&& ... args) noexcept {
      return send_(make_message<T>(from, id, std::forward<Args>(args)...));
   }

   auto send(intrusive_actor_ptr const& from, message_id const& id) noexcept {
      return send_(make_message(from, id));
   }

   auto exists() const {
      return ptr_ != nullptr;
   }

   auto release() -> void {
      ptr_ = nullptr;
   }

   auto wait_for_exit() -> wait_result {
      if(ptr_ == nullptr) {
         return { .result = wait_result::invalid_handle };
      }
      return { .result = wait_result::exited, ptr_->wait_for_exit() };
   }

private:
   auto send_(message_element*) noexcept -> enq_result;

private:
   intrusive_actor_ptr ptr_{};
};

inline constexpr wait_result NORMAL_EXIT{wait_result::exited, exit_reason::normal};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_HANDLE_H
