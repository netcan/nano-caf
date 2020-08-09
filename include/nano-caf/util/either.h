//
// Created by Darwin Yuan on 2020/8/2.
//

#ifndef NANO_CAF_EITHER_H
#define NANO_CAF_EITHER_H

#include <nano-caf/nano-caf-ns.h>
#include <utility>

NANO_CAF_NS_BEGIN

template<typename L, typename R>
struct either {
private:
   enum class state : uint8_t {
      l_active,
      r_active
   };

public:
   either(L&& l) : state_{state::l_active} {
      new (holder) L{std::move(l)};
   }
   either(R&& r) : state_{state::r_active} {
      new (holder) R{std::move(r)};
   }
   either(const L& l) : state_{state::l_active} {
      new (holder) L{l};
   }
   either(const R& r) : state_{state::r_active} {
      new (holder) R{r};
   }

   either(const either& rhs) : state_{rhs.state_} {
      switch(state_) {
         case state::l_active: new (holder) L(rhs.left()); break;
         case state::r_active: new (holder) R(rhs.right()); break;
      }
   }

   either(either&& rhs) : state_{rhs.state_} {
      switch(state_) {
         case state::l_active: new (holder) L(std::move(rhs.left())); break;
         case state::r_active: new (holder) R(std::move(rhs.right())); break;
         default: break;
      }
   }

   either& operator=(either rhs) {
      std::swap(rhs, this);
      return *this;
   }

   auto left_present() const -> bool {
      return state_ == state::l_active;
   }

   auto right_present() const -> bool {
      return state_ == state::r_active;
   }

   auto left() -> L& {
      return *reinterpret_cast<L*>(holder);
   }
   auto right() -> R& {
      return *reinterpret_cast<R*>(holder);
   }

   auto left() const -> const L& {
      return *reinterpret_cast<const L*>(holder);
   }
   auto right() const -> const R& {
      return *reinterpret_cast<const R*>(holder);
   }

   template<typename F_L, typename F_R>
   auto match(F_L&& f_l, F_R&& f_r) const {
      static_assert(std::is_invocable_v<F_L, L&>, "f_left type mismatch");
      static_assert(std::is_invocable_v<F_R, R&>, "f_right type mismatch");
      static_assert(std::is_same_v<std::invoke_result_t<F_L, L&>, std::invoke_result_t<F_R, R&>>, "result type mismatch");
      switch (state_) {
         case state::l_active: return f_l(left());
         case state::r_active: return f_r(right());
      }
   }

   ~either() {
      switch(state_) {
         case state::l_active: left().~L();; break;
         case state::r_active: right().~R();; break;
      }
   };

private:
   constexpr static size_t size = std::max(sizeof(L), sizeof(R));
   constexpr static size_t align = std::max(alignof(L), alignof(R));
   alignas(align) char holder[size];
   state state_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_EITHER_H
