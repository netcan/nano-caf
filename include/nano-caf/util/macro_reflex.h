//
// Created by Darwin Yuan on 2020/7/31.
//

#ifndef NANO_CAF_MACRO_REFLEX_H
#define NANO_CAF_MACRO_REFLEX_H

#include <maco/basic.h>
#include <maco/foreach.h>
#include <maco/aggregate.h>
#include <nano-caf/util/type_list.h>
#include <cstddef>
#include <utility>

///////////////////////////////////////////////////////////////////////////////////////////////
NANO_CAF_NS_BEGIN

namespace detail {
   template<typename T, size_t ... I>
   auto deduce_msg_field_types(std::index_sequence<I...>)
   -> type_list<typename T::template __SeCrEtE_field<I, T>::type...>;

   template<typename T>
   using msg_fields_types =
   decltype(detail::deduce_msg_field_types<T>(std::make_index_sequence<T::NuM_oF_fIeLdS>{}));
}

NANO_CAF_NS_END

////////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_field_def__(n, x)                 \
__MACO_var_full(x);                              \
template <typename T>                           \
struct __SeCrEtE_field<n, T> {                  \
   using type = decltype(T::__MACO_var_name(x)); \
   static auto get(T& obj) -> decltype(auto) { return (obj.__MACO_var_name(x)); } \
   constexpr static auto get(const T& obj) -> decltype(auto) { return (obj.__MACO_var_name(x)); } \
   constexpr static auto name() -> const char* const { return __MACO_stringify(__MACO_var_name(x)); } \
};

////////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_fields(...) \
constexpr static size_t NuM_oF_fIeLdS = __CUB_pp_size(__VA_ARGS__); \
template<size_t N, typename T> struct __SeCrEtE_field; \
__MACO_foreach(__CUB_field_def__, 0, __VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_field_def_only__(n, x) __MACO_var_full(x);

////////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_fields_only(...) __MACO_foreach(__CUB_field_def_only__, __VA_ARGS__)

#endif //NANO_CAF_MACRO_REFLEX_H
