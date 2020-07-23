//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_MESSAGE_ELEMENT_H
#define NANO_CAF_MESSAGE_ELEMENT_H

#include <nano-caf/nano-caf-ns.h>
#include "message_id.h"

NANO_CAF_NS_BEGIN

struct message_element {
   template<typename T>
   auto body() const -> T& {
      return *reinterpret_cast<T*>(const_cast<message_element*>(this));
   }

   message_element(uint32_t id, message_id::category category = message_id::category::normal)
      : message_id(id, category)
   {}

   auto is_urgent() const noexcept -> bool {
      return message_id.is_category(message_id::category::urgent);
   }
public:
   message_element* next {};
   message_id message_id;
};

NANO_CAF_NS_END

#endif //NANO_CAF_MESSAGE_ELEMENT_H
