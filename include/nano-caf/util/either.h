//
// Created by Darwin Yuan on 2020/8/2.
//

#ifndef NANO_CAF_EITHER_H
#define NANO_CAF_EITHER_H

#include <nano-caf/nano-caf-ns.h>
#include <utility>
#include <variant>

NANO_CAF_NS_BEGIN

template<typename L, typename R>
struct either : private std::variant<L, R> {
   using parent = std::variant<L, R>;
   using parent::parent;

   template<typename T, typename ... Args>
   inline constexpr auto emplace(Args&& ... args) -> T& {
      return parent::template emplace<T>(std::forward<Args>(args)...);
   }

   template<typename ... Args>
   inline constexpr auto emplace_left(Args&& ... args) -> L& {
      return parent::template emplace<L>(std::forward<Args>(args)...);
   }

   template<typename ... Args>
   inline constexpr auto emplace_right(Args&& ... args) -> R& {
      return parent::template emplace<R>(std::forward<Args>(args)...);
   }

   inline constexpr auto left_present() const -> bool {
      return parent::index() == 0;
   }

   inline constexpr auto right_present() const -> bool {
      return parent::index() == 1;
   }

   inline constexpr auto left() -> L& {
      return std::get<0>(*this);
   }

   inline constexpr auto right() -> R& {
      return std::get<1>(*this);
   }

   inline constexpr auto left() const -> const L& {
      return std::get<0>(*this);
   }

   inline constexpr auto right() const -> const R& {
      return std::get<1>(*this);
   }

   template<typename F_L, typename F_R>
   constexpr auto match(F_L&& f_l, F_R&& f_r) const {
      static_assert(std::is_invocable_v<F_L, L&>, "f_left type mismatch");
      static_assert(std::is_invocable_v<F_R, R&>, "f_right type mismatch");
      static_assert(std::is_same_v<std::invoke_result_t<F_L, L&>, std::invoke_result_t<F_R, R&>>, "result type mismatch");
      return left_present() ? f_l(left()) : f_r(right());
   }

   friend inline bool operator==(const either& lhs, const either& rhs) {
      return static_cast<const parent&>(lhs) == static_cast<const parent&>(rhs);
   }

   friend inline bool operator!=(const either& lhs, const either& rhs) {
      return !operator==(lhs, rhs);
   }

   friend inline bool operator<(const either& lhs, const either& rhs) {
      return static_cast<const parent&>(lhs) < static_cast<const parent&>(rhs);
   }

   friend inline bool operator<=(const either& lhs, const either& rhs) {
      return static_cast<const parent&>(lhs) <= static_cast<const parent&>(rhs);
   }

   friend inline bool operator>(const either& lhs, const either& rhs) {
      return static_cast<const parent&>(lhs) > static_cast<const parent&>(rhs);
   }

   friend inline bool operator>=(const either& lhs, const either& rhs) {
      return static_cast<const parent&>(lhs) >= static_cast<const parent&>(rhs);
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_EITHER_H
