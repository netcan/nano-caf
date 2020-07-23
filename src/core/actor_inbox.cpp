//
// Created by Darwin Yuan on 2020/7/22.
//

#include <nano-caf/core/actor_inbox.h>
#include <nano-caf/core/message_element.h>

NANO_CAF_NS_BEGIN

//////////////////////////////////////////////////////////////
auto actor_inbox::new_round(size_t quota, message_consumer f) noexcept -> new_round_result {
   // todo:
   urgent_queue.new_round(quota, f);
   return normal_queue.new_round(quota, f);
}

//////////////////////////////////////////////////////////////
auto actor_inbox::reload() noexcept -> void {
   auto message = lifo_inbox::take_all();
   task_list urgent, normal;
   while (message != nullptr) {
      if(message->is_urgent()) {
         urgent.push_front(message);
      } else {
         normal.push_front(message);
      }
   }
   urgent_queue.append_list(urgent);
   normal_queue.append_list(normal);
}

NANO_CAF_NS_END