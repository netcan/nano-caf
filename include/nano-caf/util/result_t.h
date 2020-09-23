//
// Created by Darwin Yuan on 2020/8/12.
//

#ifndef NANO_CAF_RESULT_T_H
#define NANO_CAF_RESULT_T_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/either.h>
#include <nano-caf/util/status_t.h>
#include <utility>

NANO_CAF_NS_BEGIN

template<typename T>
class result_t : private either<T, status_t> {
   using parent = either<T, status_t>;
public:
   constexpr result_t(T&& value) noexcept
      : parent{std::move(value)}
   {}

   constexpr result_t(const T& value) noexcept
      : parent{value}
   {}

   constexpr result_t(status_t&& value) noexcept
      : parent{std::move(value)}
   {}

   constexpr result_t(const result_t& other)
      : parent {other}
   {}

   constexpr result_t(result_t&& other) noexcept
      : parent {std::move(other)}
   {}

   template<typename ... Args>
   inline constexpr auto emplace(Args&& ... args) -> T& {
      return parent::template emplace<T>(std::forward<Args>(args)...);
   }

   using parent::operator=;

   inline constexpr auto is_ok() const noexcept -> bool {
      return parent::is_left();
   }

   inline constexpr auto operator*() -> T& {
      return parent::left();
   }

   inline constexpr auto operator*() const -> const T& {
      return parent::left();
   }

   inline constexpr auto value_or_else(const T& default_value) const -> const T& {
      return is_ok() ? operator*() : default_value;
   }

   template <typename F>
   inline constexpr auto with_value(F&& f) const -> std::invoke_result_t<F, const T&> {
      return parent::left_match(std::forward<F>(f));
   }

   inline constexpr auto failure() const -> status_t {
      return parent::is_right() ? parent::right() : status_t::ok;
   }

   template<typename F_VALUE, typename F_ERROR>
   constexpr auto match(F_VALUE&& f_value, F_ERROR&& f_error) const noexcept {
      return parent::match(std::forward<F_VALUE>(f_value), std::forward<F_ERROR>(f_error));
   }

   friend inline bool operator==(const result_t& lhs, const result_t& rhs) noexcept {
      return static_cast<const parent&>(lhs) == static_cast<const parent&>(rhs);
   }

   friend inline bool operator!=(const result_t& lhs, const result_t& rhs) noexcept {
      return !operator==(lhs, rhs);
   }

   friend inline bool operator<(const result_t& lhs, const result_t& rhs) noexcept {
      return static_cast<const parent&>(lhs) < static_cast<const parent&>(rhs);
   }

   friend inline bool operator<=(const result_t& lhs, const result_t& rhs) noexcept {
      return static_cast<const parent&>(lhs) <= static_cast<const parent&>(rhs);
   }

   friend inline bool operator>(const result_t& lhs, const result_t& rhs) noexcept {
      return static_cast<const parent&>(lhs) > static_cast<const parent&>(rhs);
   }

   friend inline bool operator>=(const result_t& lhs, const result_t& rhs) noexcept {
      return static_cast<const parent&>(lhs) >= static_cast<const parent&>(rhs);
   }
};


template<>
struct result_t<void> {
   constexpr result_t() noexcept = default;
   constexpr result_t(status_t&& value) noexcept
      : failure_{std::move(value)}
   {}

   constexpr result_t(const result_t& other) noexcept = default;
   constexpr result_t(result_t&& other) noexcept
      : failure_{std::move(other.failure_)}
   {}

   inline constexpr auto is_ok() const noexcept -> bool {
      return !failure_;
   }

   inline constexpr auto failure() const -> status_t {
      return failure_ ? *failure_ : status_t::ok;
   }

   template<typename F_VALUE, typename F_ERROR>
   constexpr auto match(F_VALUE&& f_value, F_ERROR&& f_error) const noexcept {
      return is_ok() ? f_value() : f_error(*failure_);
   }

private:
   std::optional<status_t> failure_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_RESULT_T_H
