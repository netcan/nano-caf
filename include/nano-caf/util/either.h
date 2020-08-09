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
   either(U&& u) : holder{std::move(u)}, choice_u{true} {}
   either(V&& v) : holder{std::move(v)}, choice_u{false} {}
   either(const U& u) : holder{u}, choice_u{true} {}
   either(const V& v) : holder{v}, choice_u{false} {}

   either(const either& rhs) : choice_u{rhs.choice_u} {
      if(rhs.choice_u) {
         holder.u = rhs.holder.u;
      } else {
         holder.v = rhs.holder.v;
      }
   }

   either(either&& rhs) : choice_u{rhs.choice_u} {
      if(rhs.choice_u) {
         holder.u = std::move(rhs.holder.u);
      } else {
         holder.v = std::move(rhs.holder.v);
      }
   }

   either& operator=(either rhs) {
      std::swap(rhs, this);
      return *this;
   }

   auto left_set() const -> bool {
      return choice_u;
   }

   auto right_set() const -> bool {
      return !choice_u;
   }

   auto left() const -> U& {
      return holder.u;
   }

   auto right() const -> V& {
      return holder.v;
   }

   template<typename L, typename R>
   auto match(L&& f_l, R&& f_r) const {
      static_assert(std::is_invocable_v<L, U> && std::is_invocable_v<R, V>, "type mismatch");
      static_assert(std::is_same_v<std::invoke_result_t<L, U>, std::invoke_result_t<R, V>>, "result type mismatch");
      return choice_u ? f_l(holder.u) : f_r(holder.v);
   }

   ~either() {
      if(choice_u) {
         holder.u.~U();
      } else {
         holder.v.~V();
      }
   };

private:
   union either_holder {
      either_holder() = default;
      either_holder(U&& u) : u{std::move(u)} {}
      either_holder(V&& v) : v{std::move(v)} {}
      either_holder(const U& u) : u{u} {}
      either_holder(const V& v) : v{v} {}

      U u;
      V v;
   };

   either_holder holder;
   bool choice_u{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_EITHER_H
