//
// Created by Darwin Yuan on 2020/7/31.
//

#ifndef NANO_CAF_MACRO_REFLEX_H
#define NANO_CAF_MACRO_REFLEX_H

#include <nano-caf/util/macro_basic.h>
#include <nano-caf/util/macro_pp_size.h>
#include <nano-caf/util/macro_reflex_call.h>
#include <cstddef>

////////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_keep__(...) __VA_ARGS__
#define __CUB_eat__(...)
#define __CUB_var_full(x) __CUB_keep__ x
#define __CUB_var_name(x) __CUB_eat__  x

////////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_field_def__(n, x)                 \
__CUB_var_full(x);                              \
template <typename T>                           \
struct __SeCrEtE_field<n, T> {                  \
   using type = decltype(T::__CUB_var_name(x)); \
   static auto get(T& obj) -> decltype(auto) { return (obj.__CUB_var_name(x)); } \
   constexpr static auto get(const T& obj) -> decltype(auto) { return (obj.__CUB_var_name(x)); } \
   constexpr static auto name() -> const char* const { return __CUB_stringify(__CUB_var_name(x)); } \
};

////////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_fields(...) \
constexpr static size_t NuM_oF_fIeLdS = __CUB_pp_size(__VA_ARGS__); \
template<size_t N, typename T> struct __SeCrEtE_field; \
__CUB_overload(__CUB_repeat_call_, __VA_ARGS__) (__CUB_field_def__, 0, __VA_ARGS__)

#endif //NANO_CAF_MACRO_REFLEX_H
