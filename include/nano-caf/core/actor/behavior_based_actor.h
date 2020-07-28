//
// Created by Darwin Yuan on 2020/7/29.
//

#ifndef NANO_CAF_BEHAVIOR_BASED_ACTOR_H
#define NANO_CAF_BEHAVIOR_BASED_ACTOR_H

#include <nano-caf/core/actor/actor.h>
#include <nano-caf/core/actor/behavior.h>
NANO_CAF_NS_BEGIN

struct behavior_based_actor : actor {
protected:
   virtual auto handle_message(message_element& msg) noexcept -> task_result final {
      if(behavior_.get() == nullptr) {
         auto behavior = get_behavior();
         behavior_.reset(behavior.ptr_.release());
      }

      if(behavior_.get() == nullptr) {
         return task_result::stop_all;
      }

      return behavior_->handle_msg(msg);
   }

private:
   virtual auto get_behavior() -> behavior = 0;

private:
   std::unique_ptr<detail::msg_handler> behavior_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_BEHAVIOR_BASED_ACTOR_H
