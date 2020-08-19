//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_ACTOR_HANDLE_H
#define NANO_CAF_ACTOR_HANDLE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/actor/enq_result.h>
#include <nano-caf/util/result_t.h>
#include <nano-caf/core/msg/make_message.h>
#include <nano-caf/core/msg/predefined-msgs.h>

NANO_CAF_NS_BEGIN

struct message;

struct actor_handle {
   actor_handle(intrusive_actor_ptr ptr = nullptr) noexcept : ptr_{ptr} {}

   template<typename T, message::category CATEGORY = message::normal, typename ... Args>
   auto send(Args&& ... args) noexcept {
      return send_(make_message<T, CATEGORY>(std::forward<Args>(args)...));
   }

   template<typename T, message::category CATEGORY = message::normal, typename HANDLER, typename ... Args>
   auto request(HANDLER&& handler, Args&& ... args) noexcept {
      return send_(make_request<T, CATEGORY>(std::forward<HANDLER>(handler), std::forward<Args>(args)...));
   }

   template<message::category CATEGORY = message::urgent>
   auto exit(exit_reason reason = exit_reason::normal) noexcept {
      return send_(make_message<exit_msg, CATEGORY>(reason));
   }

   template<message::category CATEGORY = message::urgent>
   auto exit_and_wait(exit_reason reason = exit_reason::normal) noexcept -> result_t<exit_reason> {
      if(auto status = exit<CATEGORY>(reason); __unlikely(status != status_t::ok)) {
         return status;
      }
      auto result = wait_for_exit();
      if(__likely(result.is_ok())) {
         release();
      }
      return result;
   }

   template<typename T, message::category CATEGORY = message::normal, typename ... Args>
   auto send(intrusive_actor_ptr from, Args&& ... args) noexcept {
      return send_(make_message<T, CATEGORY>(from, std::forward<Args>(args)...));
   }

   template<typename T, message::category CATEGORY = message::normal, typename HANDLER, typename ... Args>
   auto request(intrusive_actor_ptr from, HANDLER&& handler, Args&& ... args) noexcept {
      return send_(make_request<T, CATEGORY>(from, std::forward<HANDLER>(handler), std::forward<Args>(args)...));
   }

   auto get()             { return ptr_; }
   auto exists() const    { return ptr_ != nullptr; }
   auto release() -> void { ptr_ = nullptr; }

   auto wait_for_exit() noexcept -> result_t<exit_reason> {
      if(ptr_ == nullptr) {
         return status_t::null_pointer;
      }
      return ptr_->wait_for_exit();
   }

   ~actor_handle() noexcept { ptr_.release(); }

   inline auto operator==(actor_handle const& rhs) const noexcept -> bool {
      return ptr_ == rhs.ptr_;
   }

   inline auto operator!=(actor_handle const& rhs) const noexcept -> bool {
      return !operator==(rhs);
   }

private:
   auto send_(message*) noexcept -> status_t;

private:
   intrusive_actor_ptr ptr_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_HANDLE_H
