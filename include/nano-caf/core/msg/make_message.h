//
// Created by Darwin Yuan on 2020/8/2.
//

#ifndef NANO_CAF_MAKE_MESSAGE_H
#define NANO_CAF_MAKE_MESSAGE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message.h>
#include <utility>

NANO_CAF_NS_BEGIN

template<typename T, message_id::category CATEGORY>
class message_base {
   constexpr static auto id = message_id{T::msg_id, CATEGORY};

public:
   struct type : message {
      type() : message(id) {}
      type(intrusive_actor_ptr sender) : message(sender, id) {}
   };
};

template<typename T, message_id::category CATEGORY, typename = void>
struct message_entity : message_base<T, CATEGORY>::type {
   template<typename ... Args>
   message_entity(intrusive_actor_ptr sender, Args&&...args)
      : message_base<T, CATEGORY>::type{sender}
      , value{std::forward<Args>(args)...}{}

   template<typename ... Args>
   message_entity(Args&&...args)
      : value{std::forward<Args>(args)...}{}

   auto body_ptr() const noexcept -> const void* override {
      return reinterpret_cast<const void*>(&value);
   }

   T value;
};

template<typename T, message_id::category CATEGORY>
struct message_entity<T, CATEGORY, std::enable_if_t<std::is_class_v<T>>>
   : message_base<T, CATEGORY>::type, T {

   template<typename ... Args>
   message_entity(intrusive_actor_ptr sender, Args&&...args)
      : message_base<T, CATEGORY>::type{sender}
      , T{std::forward<Args>(args)...}{}

   template<typename ... Args>
   message_entity(Args&&...args)
      : T{std::forward<Args>(args)...} {}

   auto body_ptr() const noexcept -> const void* override {
      return reinterpret_cast<const void*>(static_cast<const T*>(this));
   }
};

template<typename T, message_id::category CATEGORY = message_id::normal, typename ... Args>
inline auto make_message(Args&&...args) -> message* {
   return new message_entity<T, CATEGORY>(std::forward<Args>(args)...);
}

template<typename T, message_id::category CATEGORY = message_id::normal, typename ... Args>
inline auto make_message(intrusive_actor_ptr sender, Args&&...args) -> message* {
   return new message_entity<T, CATEGORY>(sender, std::forward<Args>(args)...);
}

NANO_CAF_NS_END

#endif //NANO_CAF_MAKE_MESSAGE_H
