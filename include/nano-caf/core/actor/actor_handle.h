//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_ACTOR_HANDLE_H
#define NANO_CAF_ACTOR_HANDLE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/actor/enq_result.h>
#include <nano-caf/core/msg/make_message.h>
#include <nano-caf/core/actor/wait_result.h>
#include <nano-caf/core/msg/predefined-msgs.h>

NANO_CAF_NS_BEGIN

struct message;

struct actor_handle {
   actor_handle(intrusive_actor_ptr ptr = nullptr) : ptr_{ptr} {}

   template<typename T, message::category CATEGORY = message::normal, typename ... Args>
   auto send(Args&& ... args) noexcept {
      return send_(make_message<T, CATEGORY>(std::forward<Args>(args)...));
   }

   template<typename T, message::category CATEGORY = message::normal, typename HANDLER, typename ... Args>
   auto request(HANDLER&& handler, Args&& ... args) noexcept {
      return send_(make_request<T, CATEGORY>(std::forward<HANDLER>(handler), std::forward<Args>(args)...));
   }

   template<message::category CATEGORY = message::normal>
   auto exit(exit_reason reason = (CATEGORY == message::urgent ? exit_reason::kill : exit_reason::normal)) noexcept {
      return send_(make_message<exit_msg, CATEGORY>(reason));
   }

   template<typename T, message::category CATEGORY = message::normal, typename ... Args>
   auto send(intrusive_actor_ptr from, Args&& ... args) noexcept {
      return send_(make_message<T, CATEGORY>(from, std::forward<Args>(args)...));
   }

   template<typename T, message::category CATEGORY = message::normal, typename HANDLER, typename ... Args>
   auto request(intrusive_actor_ptr from, HANDLER&& handler, Args&& ... args) noexcept {
      return send_(make_request<T, CATEGORY>(from, std::forward<HANDLER>(handler), std::forward<Args>(args)...));
   }

   auto exists() const {
      return ptr_ != nullptr;
   }

   auto release() -> void {
      ptr_ = nullptr;
   }

   auto wait_for_exit() -> either<exit_reason, status_t>{
      if(ptr_ == nullptr) {
         return status_t::null_ptr;
      }
      return ptr_->wait_for_exit();
   }

   ~actor_handle() {
       ptr_.release();
   }
private:
   auto send_(message*) noexcept -> status_t;

private:
   intrusive_actor_ptr ptr_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_HANDLE_H
