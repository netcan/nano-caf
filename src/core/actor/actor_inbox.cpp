//
// Created by Darwin Yuan on 2020/7/22.
//

#include <nano-caf/core/actor/actor_inbox.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/util/likely.h>

NANO_CAF_NS_BEGIN

////////////////////////////////////////////////////////////////////////////////////////////////
auto actor_inbox::new_round(size_t quota, message_consumer f) noexcept -> new_round_result {
   reload();
   if(empty()) return 0;

   auto total = quota + urgent_queue.deficit() + normal_queue.deficit();

   auto result = urgent_queue.new_round(total, f);
   if (__unlikely(!result.has_value() || *result >= total)) {
      return result;
   }

   auto result2 = normal_queue.new_round(total - *result, f);
   if(__unlikely(!result2.has_value())) {
      return std::nullopt;
   }

   return *result + *result2;
}

//////////////////////////////////////////////////////////////
auto actor_inbox::reload() noexcept -> void {
   auto message = lifo_inbox::take_all();
   task_list urgent, normal;
   while (message != nullptr) {
      auto ptr = message;
      message = message->next_;

      if(__unlikely(ptr->is_urgent())) {
         urgent.push_front(ptr);
      } else {
         normal.push_front(ptr);
      }
   }

   urgent_queue.append_list(urgent);
   normal_queue.append_list(normal);
}

auto actor_inbox::close() -> void {
   lifo_inbox::close();
   urgent_queue.clear();
   normal_queue.clear();
}

NANO_CAF_NS_END