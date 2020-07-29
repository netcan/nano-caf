//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_MESSAGE_ELEMENT_H
#define NANO_CAF_MESSAGE_ELEMENT_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message_id.h>
#include <nano-caf/util/intrusive_ptr.h>
#include <nano-caf/core/actor/intrusive_actor_ptr.h>
#include <utility>

NANO_CAF_NS_BEGIN

struct message_element {
   message_element(const message_id& id) : msg_id{id} {}
   message_element(intrusive_actor_ptr sender, const message_id& id) : sender{sender}, msg_id{id} {}
   message_element(uint32_t id, message_id::category category = message_id::normal)
      : msg_id(id, category)
   {}

   auto is_urgent() const noexcept -> bool {
      return msg_id.is_category(message_id::urgent);
   }

   auto is_future_response() const noexcept -> bool {
      return msg_id.is_category(message_id::future);
   }

   template<typename T>
   auto body() const noexcept -> const T* {
      if(from_msg_type_to_id<T>::msg_id != get_id()) return nullptr;
      return reinterpret_cast<const T*>(body_ptr());
   }

   auto get_id() const -> msg_id_t {
      return msg_id.get_id();
   }

   virtual ~message_element() = default;

private:
   virtual auto body_ptr() const noexcept -> const void* = 0;

public:
   message_element* next {};
   intrusive_actor_ptr sender{};
   message_id msg_id;
};

   template<typename T, message_id::category CATEGORY>
   class message_base {
      constexpr static auto id = message_id{from_msg_type_to_id<T>::msg_id, CATEGORY};

   public:
      struct type : message_element {
         type() : message_element(id) {}
         type(intrusive_actor_ptr sender) : message_element(sender, id) {}
      };
   };

template<typename T, message_id::category CATEGORY, typename = void>
struct message : message_base<T, CATEGORY>::type {
   template<typename ... Args>
   message(intrusive_actor_ptr sender, Args&&...args)
      : message_base<T, CATEGORY>::type{sender}
      , value{std::forward<Args>(args)...}{}

   template<typename ... Args>
   message(Args&&...args)
      : value{std::forward<Args>(args)...}{}

   auto body_ptr() const noexcept -> const void* override {
      return reinterpret_cast<const void*>(&value);
   }

   T value;
};

template<typename T, message_id::category CATEGORY>
struct message<T, CATEGORY, std::enable_if_t<std::is_class_v<T>>>
   : message_base<T, CATEGORY>::type, T {

   template<typename ... Args>
   message(intrusive_actor_ptr sender, Args&&...args)
      : message_base<T, CATEGORY>::type{sender}
      , T{std::forward<Args>(args)...}{}

   template<typename ... Args>
   message(Args&&...args)
      : T{std::forward<Args>(args)...} {}

   auto body_ptr() const noexcept -> const void* override {
      return reinterpret_cast<const void*>(static_cast<const T*>(this));
   }
};

template<typename T, message_id::category CATEGORY = message_id::normal, typename ... Args>
inline auto make_message(Args&&...args) -> message_element* {
   return new message<T, CATEGORY>(std::forward<Args>(args)...);
}

template<typename T, message_id::category CATEGORY = message_id::normal, typename ... Args>
inline auto make_message(intrusive_actor_ptr sender, Args&&...args) -> message_element* {
   return new message<T, CATEGORY>(sender, std::forward<Args>(args)...);
}


NANO_CAF_NS_END

#endif //NANO_CAF_MESSAGE_ELEMENT_H
