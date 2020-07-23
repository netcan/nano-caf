//
// Created by Darwin Yuan on 2020/7/22.
//

#include <nano-caf/core/actor_inbox.h>
#include <nano-caf/core/message_element.h>

NANO_CAF_NS_BEGIN

//////////////////////////////////////////////////////////////
auto actor_inbox::next() noexcept -> std::unique_ptr<message_element> {
   return nullptr;
}

//////////////////////////////////////////////////////////////
auto actor_inbox::reload() noexcept -> message_element* {
   auto lifo_list = lifo_inbox::take_all();
   return lifo_list;
}

NANO_CAF_NS_END