//
// Created by Darwin Yuan on 2020/8/8.
//

#ifndef NANO_CAF_REQUEST_H
#define NANO_CAF_REQUEST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/atom.h>
#include <nano-caf/util/macro_basic.h>
#include <nano-caf/util/macro_pp_size.h>
#include <nano-caf/util/macro_reflex_call.h>
#include <nano-caf/util/callable_trait.h>

NANO_CAF_NS_BEGIN

namespace detail {
   template<typename ATOM, typename SIGNATURE>
   struct request_type {
      request_type() = delete;
      request_type(const request_type&) = delete;
      request_type(request_type&&) = delete;

      static_assert(!callable_trait<SIGNATURE>::is_variadic, "request does not support variadic arguments");
      using return_type  = typename callable_trait<SIGNATURE>::return_type;
      using args_type    = typename callable_trait<SIGNATURE>::decayed_args_type;
      using pattern_type = typename callable_trait<SIGNATURE>::decayed_args_type::template prepend_type<ATOM>;
   };
}

namespace detail {
   template<typename T, size_t ... I>
   auto deduce_method_atoms(std::index_sequence<I...>)
   -> type_list<typename T::template __SeCrEtE_method<I, T>::method_type...>;

   template<typename T>
   using method_atoms = decltype(detail::deduce_method_atoms<T>(std::make_index_sequence<T::total_methods>{}));
}

#define __CUB_method_name(x)      __CUB_1st   x
#define __CUB_method_signature(x) __CUB_rest  x

#define __CUB_atom_type(x) __CUB_paste(__CUB_method_name(x), _atom)
////////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_actor_method(n, x) \
struct __CUB_atom_type(x); \
template <typename T> struct __SeCrEtE_method<n, T>               \
   : detail::request_type<__CUB_atom_type(x), auto __CUB_method_signature(x)> {                      \
   using method_type = __CUB_atom_type(x); \
   constexpr static auto name() -> const char* const { return __CUB_stringify(__CUB_method_name(x)); } \
}; \
struct __CUB_atom_type(x) : atom_signature { \
   using type = __SeCrEtE_method<n, __SeCrEtE_tHiS_tYpe>; \
}; \
constexpr static __CUB_atom_type(x) __CUB_method_name(x);

///////////////////////////////////////////////////////////////////////////////////////////////
#define __CAF_actor_interface(name, ...)                                                 \
struct name {                                                                            \
private:                                                                                 \
   using __SeCrEtE_tHiS_tYpe = name;                                                     \
public:                                                                                  \
   template <size_t, typename> struct __SeCrEtE_method;                                  \
   constexpr static size_t total_methods = __CUB_pp_size(__VA_ARGS__);                   \
   __CUB_overload(__CUB_repeat_call_, __VA_ARGS__) (__CUB_actor_method, 0, __VA_ARGS__); \
}

NANO_CAF_NS_END

#endif //NANO_CAF_REQUEST_H
