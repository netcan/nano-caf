//
// Created by Darwin Yuan on 2020/7/23.
//

#ifndef NANO_CAF_SCHED_ACTOR_H
#define NANO_CAF_SCHED_ACTOR_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/thread_pool/resumable.h>
#include <nano-caf/core/actor/actor_inbox.h>
#include <nano-caf/core/cache_line_size.h>
#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/actor/exit_reason.h>
#include <nano-caf/core/actor/actor_handle.h>

NANO_CAF_NS_BEGIN

struct sched_actor
   : private actor_inbox
   , resumable {

   sched_actor(bool register_to_context = false);
   ~sched_actor();

   using actor_inbox::enqueue;
   using actor_inbox::blocked;
   auto resume() noexcept  -> bool override;

protected:
   auto exit_(exit_reason reason) -> void {
      if(!flags_.exiting_flag) {
         flags_.exiting_flag = 1;
         reason_ = reason;
      }
   }
private:
   auto handle_message_internal(message& msg) noexcept -> task_result;
   virtual auto user_defined_handle_msg(message&) noexcept -> task_result {
      return task_result::done;
   }

   virtual auto init_handler() noexcept -> void {}
   virtual auto exit_handler() noexcept -> void {}

private:
   auto intrusive_ptr_add_ref_impl() noexcept -> void override {
      intrusive_ptr_add_ref(to_ctl());
   }
   auto intrusive_ptr_release_impl() noexcept -> void override {
      intrusive_ptr_release(to_ctl());
   }

protected:
   auto to_ctl() const noexcept -> actor_control_block* {
      return const_cast<actor_control_block*>(
         reinterpret_cast<const actor_control_block*>(
            (reinterpret_cast<const char*>(this) - CACHE_LINE_SIZE)));
   }

   auto get_current_sender() const noexcept -> actor_handle {
      if(current_message_ == nullptr) return intrusive_actor_ptr{};
      return current_message_->sender_;
   }

   auto user_timer_created() {
      flags_.timer_created = 1;
   }
private:
   message* current_message_{};
   struct {
      uint8_t init_flag:1;
      uint8_t exiting_flag:1;
      uint8_t registered:1;
      uint8_t timer_created:1;
   } flags_{};

protected:
   exit_reason reason_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_SCHED_ACTOR_H
