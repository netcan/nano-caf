//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_MESSAGE_ELEMENT_H
#define NANO_CAF_MESSAGE_ELEMENT_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/message_id.h>
#include <nano-caf/util/intrusive_ptr.h>
#include <nano-caf/core/actor/intrusive_actor_ptr.h>
#include <utility>

NANO_CAF_NS_BEGIN

struct message_element {
   message_element(const message_id& id) : message_id{id} {}
   message_element(const intrusive_actor_ptr& sender, const message_id& id) : sender{sender}, message_id{id} {}
   message_element(uint32_t id, message_id::category category = message_id::category::normal)
      : message_id(id, category)
   {}

   auto is_urgent() const noexcept -> bool {
      return message_id.is_category(message_id::category::urgent);
   }

   template<typename T>
   auto body() const noexcept -> const T* {
      return reinterpret_cast<const T*>(body_ptr());
   }

   virtual ~message_element() = default;

private:
   virtual auto body_ptr() const noexcept -> const void* = 0;

public:
   message_element* next {};
   intrusive_actor_ptr sender{};
   message_id message_id;
};


template<typename T, typename = void>
struct message : message_element {
   template<typename ... Args>
   message(const intrusive_actor_ptr& sender, const struct message_id& id, Args&&...args)
      : message_element(sender, id)
      , value(std::forward<Args>(args)...){}

   template<typename ... Args>
   message(const struct message_id& id, Args&&...args)
      : message_element(id)
      , value(std::forward<Args>(args)...){}

   auto body_ptr() const noexcept -> const void* override {
      return reinterpret_cast<const void*>(&value);
   }

   T value;
};

template<typename T>
struct message<T, std::enable_if_t<std::is_class_v<T>>> : message_element, T {
   template<typename ... Args>
   message(const intrusive_actor_ptr& sender, const struct message_id& id, Args&&...args)
      : message_element(sender, id)
      , T(std::forward<Args>(args)...){}

   template<typename ... Args>
   message(const struct message_id& id, Args&&...args)
      : message_element(id)
      , T(std::forward<Args>(args)...){}

   auto body_ptr() const noexcept -> const void* override {
      return reinterpret_cast<const void*>(static_cast<const T*>(this));
   }
};

template<typename T>
struct message<T*> : message_element {
   template<typename ... Args>
   message(const intrusive_actor_ptr& sender, const struct message_id& id, Args&&...args)
      : message_element(sender, id)
      , T(std::forward<Args>(args)...){}

   template<typename ... Args>
   message(const struct message_id& id, Args&&...args)
      : message_element(id)
      , T(std::forward<Args>(args)...){}

   auto body_ptr() const noexcept -> const void* override {
      return reinterpret_cast<const void*>(static_cast<const T*>(this));
   }

   ~message() {
      delete value;
   }
private:
   T* value;
};

template<>
struct message<void> : message_element {
   message(const intrusive_actor_ptr& sender, const struct message_id& id)
      : message_element(sender, id) {}

   message(const struct message_id& id)
      : message_element(id) {}

   auto body_ptr() const noexcept -> const void* override {
      return nullptr;
   }
};

template<typename T, typename ... Args>
inline auto make_message(const message_id& id, Args&&...args) -> message_element* {
   return new message<T>(id, std::forward<Args>(args)...);
}

template<typename T, typename ... Args>
inline auto make_message(intrusive_actor_ptr sender, const message_id& id, Args&&...args) -> message_element* {
   return new message<T>(sender, id, std::forward<Args>(args)...);
}

inline auto make_message(const message_id& id) -> message_element* {
   return new message<void>(id);
}

inline auto make_message(intrusive_actor_ptr sender, const message_id& id) -> message_element* {
   return new message<void>(sender, id);
}

NANO_CAF_NS_END

#endif //NANO_CAF_MESSAGE_ELEMENT_H
