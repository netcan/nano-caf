//
// Created by Darwin Yuan on 2020/7/23.
//

#ifndef NANO_CAF_SCHED_ACTOR_H
#define NANO_CAF_SCHED_ACTOR_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/resumable.h>
#include <nano-caf/core/actor/actor_inbox.h>
#include <nano-caf/core/cache_line_size.h>
#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/actor/exit_reason.h>
#include <nano-caf/core/actor/actor_handle.h>

NANO_CAF_NS_BEGIN

struct sched_actor
   : resumable
   , private actor_inbox {

   sched_actor(bool register_to_context = false);
   ~sched_actor();

   using actor_inbox::enqueue;
   using actor_inbox::blocked;
   auto resume() noexcept  -> resumable::result override;

protected:
   auto exit_(exit_reason reason) -> void {
      if(!(flags_ & exiting_flag)) {
         flags_ |= exiting_flag;
         reason_ = reason;
      }
   }
private:
   enum : uint32_t {
      exiting_flag = 0x0000'0001,
   };

   auto handle_message_internal(message& msg) noexcept -> task_result;
   virtual auto user_defined_handle_msg(message&) noexcept -> task_result {
      return task_result::done;
   }

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
      return current_message_->sender;
   }

private:
   message* current_message_{};
   uint32_t flags_{};
   exit_reason reason_;
   bool registered_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_SCHED_ACTOR_H
