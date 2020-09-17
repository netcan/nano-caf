//
// Created by Darwin Yuan on 2020/9/17.
//

#ifndef NANO_CAF_AWAITABLE_TRAIT_H
#define NANO_CAF_AWAITABLE_TRAIT_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/request_reply.h>
#include <coroutine>

NANO_CAF_NS_BEGIN

namespace detail {
   template<typename T>
   struct is_coroutine_handle : std::false_type {};

   template<typename T>
   struct is_coroutine_handle<std::coroutine_handle<T>> : std::true_type {};

   template<typename T>
   constexpr bool is_coroutine_handle_v = is_coroutine_handle<T>::value;

   template<typename T>
   concept valid_await_suspend_result =
      std::is_void_v<T> ||
      std::is_same_v<bool, T> ||
      is_coroutine_handle_v<T>;
}

template<typename T, typename P>
concept awaiter_concept = requires(T value) {
   { value.await_ready() } -> std::same_as<bool>;
   { value.await_suspend(std::declval<std::coroutine_handle<P>>()) } -> detail::valid_await_suspend_result;
   { value.await_resume() };
};

template<typename T>
concept has_co_await = requires(T&& value) {
   std::forward<T>(value).operator co_await();
};

template<typename T>
concept has_global_co_await = requires(T&& value) {
   operator co_await(std::forward<T>(value));
};

namespace detail {
   template<has_co_await T>
   auto get_awaiter(T&& value) -> decltype(auto) {
      return std::forward<T>(value).operator co_await();
   }

   template<has_global_co_await T>
   auto get_awaiter(T&& value) -> decltype(auto) {
      return operator co_await(std::forward<T>(value));
   }

   template<awaiter_concept<void> T>
   auto get_awaiter(T&& value) -> decltype(auto) {
      return std::forward<T>(value);
   }
}

template<typename T, typename P>
concept awaitable_concept = has_co_await<T> || has_global_co_await<T> || awaiter_concept<T, P>;

template<typename T>
struct awaitable_traits {
   using awaiter_t = decltype(detail::get_awaiter(std::declval<T>()));
   using await_result_t = decltype(std::declval<awaiter_t>().await_resume());
};

template<typename T>
using await_result_t = typename awaitable_traits<T>::await_result_t;

template<typename T>
concept void_awaitable = std::is_void_v<await_result_t<T>>;

template<typename T>
concept non_void_awaitable = !void_awaitable<T>;

NANO_CAF_NS_END

#endif //NANO_CAF_AWAITABLE_TRAIT_H
