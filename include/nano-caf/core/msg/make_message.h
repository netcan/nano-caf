//
// Created by Darwin Yuan on 2020/8/2.
//

#ifndef NANO_CAF_MAKE_MESSAGE_H
#define NANO_CAF_MAKE_MESSAGE_H

#include <nano-caf/core/msg/message.h>
#include <nano-caf/util/result_trait.h>
#include <future>

NANO_CAF_NS_BEGIN

template<typename T, message::category CATEGORY>
struct message_base : message {
   message_base() : message(T::type_id, CATEGORY) {}
   message_base(intrusive_actor_ptr sender)
         : message(sender, T::type_id, CATEGORY) {}

};

template<typename T, message::category CATEGORY, typename = void>
struct message_entity : message_base<T, CATEGORY> {
   template<typename ... Args>
   message_entity(intrusive_actor_ptr sender, Args&&...args)
      : message_base<T, CATEGORY>{sender}
      , value{std::forward<Args>(args)...}{}

   template<typename ... Args>
   message_entity(Args&&...args)
      : value{std::forward<Args>(args)...}{}

   auto body_ptr() const noexcept -> const void* override {
      return reinterpret_cast<const void*>(&value);
   }

   auto body_ptr() noexcept -> void* override {
      return reinterpret_cast<void*>(&value);
   }

   T value;
};

template<typename T, message::category CATEGORY>
struct message_entity<T, CATEGORY, std::enable_if_t<std::is_class_v<T>>>
   : message_base<T, CATEGORY>, T {

   template<typename ... Args>
   message_entity(intrusive_actor_ptr sender, Args&&...args)
      : message_base<T, CATEGORY>{sender}
      , T{std::forward<Args>(args)...}{}

   template<typename ... Args>
   message_entity(Args&&...args)
      : T{std::forward<Args>(args)...} {}

   auto body_ptr() noexcept -> void* override {
      return reinterpret_cast<void*>(static_cast<T*>(this));
   }

   auto body_ptr() const noexcept -> const void* override {
      return reinterpret_cast<const void*>(static_cast<const T*>(this));
   }
};

template<typename T, typename HANDLER, message::category CATEGORY>
struct request_entity : message_entity<T, CATEGORY> {
   using parent = message_entity<T, CATEGORY>;
   using real_handler_t = std::decay_t<HANDLER>;

   template<typename ... Args>
   request_entity(intrusive_actor_ptr sender, HANDLER&& handler, Args&&...args)
      : parent{sender, std::forward<Args>(args)...}
      , handler_{std::move(handler)} {}

   template<typename ... Args>
   request_entity(HANDLER&& handler, Args&&...args)
   : parent{std::forward<Args>(args)...}
   , handler_{std::move(handler)}
   {}

   auto handler_ptr() const noexcept -> void* override {
      return reinterpret_cast<void*>(const_cast<real_handler_t*>(&handler_));
   }

   using result_type = func_result_t<typename T::result_type>;
   static_assert(std::is_base_of_v<request_result_handler<result_type>, real_handler_t>);
   real_handler_t handler_;
};

template<typename T, message::category CATEGORY = message::normal, typename HANDLER, typename ... Args>
inline auto make_request(HANDLER&& handler, Args&&...args) -> message* {
   return new request_entity<T, HANDLER, static_cast<message::category>(CATEGORY | message::request_mask)>
      (std::forward<HANDLER>(handler), std::forward<Args>(args)...);
}

template<typename T, message::category CATEGORY = message::normal, typename HANDLER, typename ... Args>
inline auto make_request(intrusive_actor_ptr sender, HANDLER&& handler, Args&&...args) -> message* {
   return new request_entity<T, HANDLER, static_cast<message::category>(CATEGORY | message::request_mask)>
         (sender, std::forward<HANDLER>(handler), std::forward<Args>(args)...);
}

template<typename T, message::category CATEGORY = message::normal, typename ... Args>
inline auto make_message(Args&&...args) -> message* {
   return new message_entity<T, CATEGORY>(std::forward<Args>(args)...);
}

template<typename T, message::category CATEGORY = message::normal, typename ... Args>
inline auto make_message(intrusive_actor_ptr sender, Args&&...args) -> message* {
   return new message_entity<T, CATEGORY>(sender, std::forward<Args>(args)...);
}

NANO_CAF_NS_END

#endif //NANO_CAF_MAKE_MESSAGE_H
