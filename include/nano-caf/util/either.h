//
// Created by Darwin Yuan on 2020/8/2.
//

#ifndef NANO_CAF_EITHER_H
#define NANO_CAF_EITHER_H

#include <nano-caf/nano-caf-ns.h>
#include <utility>

NANO_CAF_NS_BEGIN

template<typename U, typename V>
struct either {
   either(U&& u) : state{U_ACTIVE} {
      new (holder) U{std::move(u)};
   }
   either(V&& v) : state{V_ACTIVE} {
      new (holder) V{std::move(v)};
   }
   either(const U& u) : state{U_ACTIVE} {
      new (holder) U{u};
   }
   either(const V& v) : state{V_ACTIVE} {
      new (holder) V{v};
   }

   either(const either& rhs) : state{rhs.state} {
      switch(state) {
         case U_ACTIVE:
            new (holder) U(rhs.left()); break;
         case V_ACTIVE:
            new (&holder.v) V(rhs.right()); break;
         default: break;
      }
   }

   either(either&& rhs) : state{rhs.state} {
      switch(state) {
         case U_ACTIVE: new (holder) U(std::move(rhs.left())); break;
         case V_ACTIVE: new (holder) V(std::move(rhs.right())); break;
         default: break;
      }
      rhs.state = INIT;
   }

   either& operator=(either rhs) {
      std::swap(rhs, this);
      return *this;
   }

   auto left_set() const -> bool {
      return state == U_ACTIVE;
   }

   auto right_set() const -> bool {
      return state == V_ACTIVE;
   }

   auto left() -> U& {
      return *reinterpret_cast<U*>(holder);
   }
   auto right() -> V& {
      return *reinterpret_cast<V*>(holder);
   }

   auto left() const -> const U& {
      return *reinterpret_cast<const U*>(holder);
   }
   auto right() const -> const V& {
      return *reinterpret_cast<const V*>(holder);
   }

   template<typename L, typename R>
   auto match(L&& f_l, R&& f_r) {
      static_assert(std::is_invocable_v<L, U&>, "f_left type mismatch");
      static_assert(std::is_invocable_v<R, V&>, "f_right type mismatch");
      static_assert(std::is_same_v<std::invoke_result_t<L, U&>, std::invoke_result_t<R, V&>>, "result type mismatch");
      switch (state) {
         case U_ACTIVE: return f_l(left());
         case V_ACTIVE: return f_r(right());
         default: {
            // error
            return f_r(right());
         }
      }
   }

   ~either() {
      switch(state) {
         case U_ACTIVE: left().~U();; break;
         case V_ACTIVE: right().~V();; break;
         default: break;
      }
   };

private:
   constexpr static size_t size = std::max(sizeof(U), sizeof(V));
   constexpr static size_t align = std::max(alignof(U), alignof(V));
   alignas(align) char holder[size];

   enum {
     INIT,
     U_ACTIVE,
     V_ACTIVE
   } state{INIT};
};

NANO_CAF_NS_END

#endif //NANO_CAF_EITHER_H
