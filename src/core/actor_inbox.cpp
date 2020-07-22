//
// Created by Darwin Yuan on 2020/7/22.
//

#include <nano-caf/core/actor_inbox.h>
#include <nano-caf/core/message_element.h>

NANO_CAF_NS_BEGIN

//////////////////////////////////////////////////////////////
auto actor_inbox::next() -> message_element* {
   if(head != nullptr) {
      auto result = head;
      head = head->next;
      return result;
   }

   return reload();
}

//////////////////////////////////////////////////////////////
auto actor_inbox::reload() noexcept -> message_element* {
   auto lifo_list = lifo_inbox::take_all();
   while (lifo_list != nullptr) {
      // return the last
      if(lifo_list->next == nullptr) break;

      auto elem = lifo_list;
      lifo_list = lifo_list->next;

      elem->next = head;
      head = elem;
   }

   return lifo_list;
}

NANO_CAF_NS_END