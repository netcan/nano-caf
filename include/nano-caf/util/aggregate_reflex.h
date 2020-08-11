//
// Created by Darwin Yuan on 2020/8/1.
//

#ifndef NANO_CAF_AGGREGATE_REFLEX_H
#define NANO_CAF_AGGREGATE_REFLEX_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/type_list.h>
#include <nano-caf/util/aggregate_fields_type.h>
#include <type_traits>
#include <nano-caf/util/supress_warning.h>

NANO_CAF_NS_BEGIN

namespace detail {
   struct universal_type {
      template<typename T> operator T() {}
   };

   template<typename T, typename = std::enable_if_t<std::is_aggregate_v<T>>, typename ... Ts>
   struct aggregate_fields_number {
      constexpr static size_t size = sizeof...(Ts) - 1;
   };

DISABLE_WARNING_PUSH
#ifdef __GNUG__
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
   template<typename T, typename ... Ts>
   struct aggregate_fields_number<T, std::enable_if_t<std::is_aggregate_v<T> &&
      std::is_same_v<T, decltype(T{Ts{}...})>>
      , Ts...> {
      constexpr static size_t size = aggregate_fields_number<T, void, Ts..., universal_type>::size;
   };
DISABLE_WARNING_POP

}

template<typename T, typename = std::enable_if_t<std::is_aggregate_v<T>>>
struct aggregate_trait {
   constexpr static size_t num_of_fields = detail::aggregate_fields_number<T>::size;
   using fields_types = typename detail::aggregate_fields_type<num_of_fields, T>::type;

   template <typename F>
   static auto call(const T& obj, F&& f) {
      return detail::aggregate_fields_type<num_of_fields, T>::call(obj, std::forward<F>(f));
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_AGGREGATE_REFLEX_H
