//
// Created by Darwin Yuan on 2020/7/23.
//

#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/system_actor_context.h>
#include <nano-caf/core/msg/predefined-msgs.h>

NANO_CAF_NS_BEGIN

constexpr size_t max_throughput = 3;

/////////////////////////////////////////////////////////////////////////////////////////////
sched_actor::sched_actor(bool register_to_context) {
   if(register_to_context) {
      to_ctl()->context().register_actor();
      flags_.registered = 1;
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////
sched_actor::~sched_actor() {
   if(flags_.registered) {
      to_ctl()->context().deregister_actor();
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto sched_actor::resume() noexcept  -> bool {
   size_t consumed_msgs = 0;

   while (consumed_msgs < max_throughput) {
      if(actor_inbox::empty() && actor_inbox::try_block()) {
         return true;
      }

      auto result = actor_inbox::new_round(max_throughput - consumed_msgs,
         [&, this](message& msg) {
            current_message_ = &msg;
            auto result  = handle_message_internal(msg);
            current_message_ = nullptr;
            return result;
      });

      if(__unlikely(!result)) {
         if(flags_.timer_created) {
            to_ctl()->context().clear_actor_timer(to_ctl());;
         }
         exit_handler();
         to_ctl()->on_exit(reason_);
         return true;
      }

      consumed_msgs += *result;
   }

   if(actor_inbox::empty() && actor_inbox::try_block()) {
      return true;
   }

   return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto sched_actor::handle_message_internal(message& msg) noexcept -> task_result {
   auto result = user_defined_handle_msg(msg);
   if(__unlikely(msg.msg_type_id_ == exit_msg::type_id)) {
      exit_(msg.body<exit_msg>()->reason);
   } else if(__unlikely(result == task_result::done)) {
      spdlog::info("sched_actor exit");
      exit_(exit_reason::normal);
   }

   if(__unlikely(flags_.exiting_flag)) {
      actor_inbox::close();
      return task_result::done;
   }

   return result;
}


NANO_CAF_NS_END