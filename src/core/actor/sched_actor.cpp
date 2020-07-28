//
// Created by Darwin Yuan on 2020/7/23.
//

#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_context.h>

NANO_CAF_NS_BEGIN

constexpr size_t max_throughput = 3;

/////////////////////////////////////////////////////////////////////////////////////////////
sched_actor::sched_actor(bool register_to_context)
   : registered_(register_to_context) {
   if(register_to_context) {
      to_ctl()->context().register_actor();
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////
sched_actor::~sched_actor() {
   if(registered_) {
      to_ctl()->context().deregister_actor();
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto sched_actor::resume() noexcept  -> resumable::result {
   size_t consumed_msgs = 0;

   while (consumed_msgs < max_throughput) {
      if(actor_inbox::empty() && actor_inbox::try_block()) {
         return resumable::result::awaiting_message;
      }
      auto result = actor_inbox::new_round(max_throughput - consumed_msgs,
         [this](const message_element& msg) {
            current_message_ = const_cast<message_element*>(&msg);
            auto result  = handle_message_internal(msg);
            current_message_ = nullptr;
            return result;
      });

      if(result.stop_all) {
         return result::done;
      }

      consumed_msgs += result.consumed_items;
   }

   if(actor_inbox::empty() && actor_inbox::try_block()) {
      return resumable::result::awaiting_message;
   }

   return resumable::result::resume_later;
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto sched_actor::handle_message_internal(const message_element& msg) noexcept -> task_result {
   user_defined_handle_msg(msg);
   if(msg.message_id == EXIT_MSG) {
      // todo: cause
      exit_(exit_reason::user_shutdown);
   }

   if(flags_ & exiting_flag) {
      actor_inbox::close();
      return task_result::stop_all;
   }

   return task_result::resume;
}


NANO_CAF_NS_END