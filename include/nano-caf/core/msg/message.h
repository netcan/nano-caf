//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_MESSAGE_H
#define NANO_CAF_MESSAGE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message_id.h>
#include <nano-caf/util/intrusive_ptr.h>
#include <nano-caf/util/type_id_t.h>
#include <nano-caf/core/actor/intrusive_actor_ptr.h>
#include <utility>

NANO_CAF_NS_BEGIN

class message {
   enum : uint64_t {
      normal_mask = uint64_t(1) << 0,
      urgent_mask = uint64_t(1) << 1,
      future_mask = uint64_t(1) << 2,
   };

   enum : uint64_t {
      future = future_mask | normal_mask
   };

public:
   enum category : uint64_t {
      normal = normal_mask,
      urgent = urgent_mask,
   };

   message(type_id_t type_id,  category cat = normal)
      : msg_type_id_(type_id)
      , category_(cat)
   {}

   message(intrusive_actor_ptr sender, type_id_t type_id, category cat = normal)
      : sender_{sender}
      , category_(cat)
      , msg_type_id_(type_id)
   {}

   auto is_urgent() const noexcept -> bool {
      return (category_ & urgent_mask);
   }

   auto is_future_response() const noexcept -> bool {
      return (category_ & future_mask);
   }

   template<typename T>
   auto body() const noexcept -> const T* {
      if(type_id<T> != msg_type_id_) return nullptr;
      return reinterpret_cast<const T*>(body_ptr());
   }

   virtual ~message() = default;

private:
   virtual auto body_ptr() const noexcept -> const void* = 0;

   template <typename F, typename R>
   friend struct async_object;

public:
   message* next_ {};

public:
   intrusive_actor_ptr sender_{};
   category category_;

   const type_id_t msg_type_id_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_MESSAGE_H
