//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_MESSAGE_H
#define NANO_CAF_MESSAGE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message_id.h>
#include <nano-caf/util/intrusive_ptr.h>
#include <nano-caf/core/actor/intrusive_actor_ptr.h>
#include <utility>

NANO_CAF_NS_BEGIN

struct message {
   message(const message_id& id) : msg_id{id} {}
   message(intrusive_actor_ptr sender, const message_id& id)
      : sender{sender}
      , msg_id{id}
   {}

   message(uint32_t id, message_id::category category = message_id::normal)
      : msg_id(id, category)
   {}

   auto is_urgent() const noexcept -> bool {
      return msg_id.is_category(message_id::urgent);
   }

   auto is_future_response() const noexcept -> bool {
      return msg_id.test_flag(message_id::future_mask);
   }

   template<typename T>
   auto body() const noexcept -> const T* {
      if(T::msg_id != get_id()) return nullptr;
      return reinterpret_cast<const T*>(body_ptr());
   }

   auto get_id() const -> msg_id_t {
      return msg_id.get_id();
   }

   virtual ~message() = default;

private:
   virtual auto body_ptr() const noexcept -> const void* = 0;

public:
   message* next {};
   intrusive_actor_ptr sender{};
   message_id msg_id;
};

NANO_CAF_NS_END

#endif //NANO_CAF_MESSAGE_H
