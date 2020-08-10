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
class either : private std::variant<L, R> {
   using parent = std::variant<L, R>;
public:
   struct left_tag {};
   struct right_tag{};

   constexpr either(L&& value) noexcept
      : parent{std::move(value)}
   {}

   constexpr either(R&& value) noexcept
      : parent{std::move(value)}
   {}

   constexpr either(const L& value) noexcept
      : parent{value}
   {}

   constexpr either(const R& value) noexcept
      : parent{value}
   {}

   template<typename ... Args>
   constexpr either(left_tag, Args&&...args)
      : parent{std::in_place_index_t<0>{}, std::forward<Args>(args)...}
   {}

   template<typename ... Args>
   constexpr either(right_tag, Args&&...args)
      : parent{std::in_place_index_t<1>{}, std::forward<Args>(args)...}
   {}

   constexpr either(const either& other)
      : parent {other}
   {}

   constexpr either(either&& other) noexcept
      : parent {std::move(other)}
   {}

   template<typename T, typename ... Args>
   inline constexpr auto emplace(Args&& ... args) -> T& {
      return parent::template emplace<T>(std::forward<Args>(args)...);
   }

   template<typename ... Args>
   inline constexpr auto emplace_left(Args&& ... args) -> L& {
      return parent::template emplace<0>(std::forward<Args>(args)...);
   }

   template<typename ... Args>
   inline constexpr auto emplace_right(Args&& ... args) -> R& {
      return parent::template emplace<1>(std::forward<Args>(args)...);
   }

   inline constexpr auto is_left() const noexcept -> bool {
      return parent::index() == 0;
   }

   inline constexpr auto is_right() const noexcept -> bool {
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

   inline constexpr auto left(const L& default_l) const -> const L& {
      return is_left() ? left() : default_l;
   }

   inline constexpr auto right() const -> const R& {
      return std::get<1>(*this);
   }

   inline constexpr auto right(const R& default_r) const -> const R& {
      return is_right() ? right() : default_r;
   }

   template<typename F_L, typename F_R>
   constexpr auto match(F_L&& f_l, F_R&& f_r) const noexcept {
      static_assert(std::is_invocable_v<F_L, const L&>, "f_left type mismatch");
      static_assert(std::is_invocable_v<F_R, const R&>, "f_right type mismatch");
      static_assert(std::is_same_v<std::invoke_result_t<F_L, const L&>, std::invoke_result_t<F_R, const R&>>, "result type mismatch");
      return is_left() ? f_l(left()) : f_r(right());
   }

   friend inline bool operator==(const either& lhs, const either& rhs) noexcept {
      return static_cast<const parent&>(lhs) == static_cast<const parent&>(rhs);
   }

   friend inline bool operator!=(const either& lhs, const either& rhs) noexcept {
      return !operator==(lhs, rhs);
   }

   friend inline bool operator<(const either& lhs, const either& rhs) noexcept {
      return static_cast<const parent&>(lhs) < static_cast<const parent&>(rhs);
   }

   friend inline bool operator<=(const either& lhs, const either& rhs) noexcept {
      return static_cast<const parent&>(lhs) <= static_cast<const parent&>(rhs);
   }

   friend inline bool operator>(const either& lhs, const either& rhs) noexcept {
      return static_cast<const parent&>(lhs) > static_cast<const parent&>(rhs);
   }

   friend inline bool operator>=(const either& lhs, const either& rhs) noexcept {
      return static_cast<const parent&>(lhs) >= static_cast<const parent&>(rhs);
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_EITHER_H
