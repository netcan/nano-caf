//
// Created by Darwin Yuan on 2020/8/1.
//

#ifndef NANO_CAF_AGGREGATE_REFLEX_H
#define NANO_CAF_AGGREGATE_REFLEX_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/type_list.h>
#include <nano-caf/util/aggregate_fields_type.h>
#include <type_traits>

NANO_CAF_NS_BEGIN

namespace detail {
   struct universal_type {
      template<typename T> operator T() {}
   };

   template<typename T, typename = std::enable_if_t<std::is_aggregate_v<T>>, typename ... Ts>
   struct aggregate_fields_number {
      constexpr static size_t size = sizeof...(Ts) - 1;
   };

   template<typename T, typename ... Ts>
   struct aggregate_fields_number<T, std::enable_if_t<std::is_aggregate_v<T> && std::is_same_v<T, decltype(T{Ts{}...})>>, Ts...> {
      constexpr static size_t size = aggregate_fields_number<T, void, Ts..., universal_type>::size;
   };
}

template<typename T, typename = std::enable_if_t<std::is_aggregate_v<T>>>
struct aggregate_info {
   constexpr static size_t size = detail::aggregate_fields_number<T>::size;
   using fields_type = typename detail::aggregate_fields_type<size, T>::type;

   template <typename F>
   static auto call(T& obj, F&& f) {
      return detail::aggregate_fields_type<size, T>::call(obj, std::forward<F>(f));
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_AGGREGATE_REFLEX_H
