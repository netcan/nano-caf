//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_MESSAGE_H
#define NANO_CAF_MESSAGE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/type_id_t.h>
#include <nano-caf/core/await/abstract_promise.h>
#include <nano-caf/core/actor/weak_actor_ptr.h>
#include <nano-caf/util/status_t.h>
#include <nano-caf/util/either.h>
#include <nano-caf/util/result_trait.h>
#include <utility>

NANO_CAF_NS_BEGIN

template<typename T, typename = void>
constexpr bool Is_Request = false;

template<typename T>
constexpr bool Is_Request<T, std::enable_if_t<T::Is_Request>> = true;

struct message {
   enum : uint64_t {
      normal_mask  = uint64_t(1) << 0,
      urgent_mask  = uint64_t(1) << 1,
      future_mask  = uint64_t(1) << 2,
      request_mask = uint64_t(1) << 3,
      reply_mask   = uint64_t(1) << 4,
   };

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
      , msg_type_id_(type_id)
      , category_(cat)
   {}

   auto is_urgent() const noexcept -> bool {
      return (category_ & urgent_mask);
   }

   auto is_request() const noexcept -> bool {
      return (category_ & request_mask);
   }

   template<typename T>
   auto body() noexcept -> T* {
      if(T::type_id != msg_type_id_) return nullptr;
      return reinterpret_cast<T*>(body_ptr());
   }

   template<typename T>
   auto body() const noexcept -> const T* {
      if(T::type_id != msg_type_id_) return nullptr;
      return reinterpret_cast<const T*>(body_ptr());
   }

   template<typename T, typename R = typename T::result_type, typename = std::enable_if_t<Is_Request<T>>>
   auto get_promise() -> abstract_promise<R>* {
      return reinterpret_cast<abstract_promise<R>*>(get_promise_ptr());
   }

   virtual ~message() = default;

private:
   virtual auto body_ptr() noexcept -> void* = 0;
   virtual auto body_ptr() const noexcept -> const void* = 0;
   virtual auto get_promise_ptr() const noexcept -> void* {
      return nullptr;
   }

public:
   message* next_ {};

public:
   weak_actor_ptr sender_{};
   const type_id_t msg_type_id_;
   category category_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_MESSAGE_H
