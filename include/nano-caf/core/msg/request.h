//
// Created by Darwin Yuan on 2020/8/8.
//

#ifndef NANO_CAF_REQUEST_H
#define NANO_CAF_REQUEST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/atom.h>
#include <maco/foreach.h>
#include <nano-caf/util/callable_trait.h>
#include <nano-caf/util/type_list.h>
#include <nano-caf/util/type_id_t.h>

NANO_CAF_NS_BEGIN

namespace detail {
   struct request_signature{};

   template<typename ATOM, typename SIGNATURE>
   struct request_type {
      request_type() = delete;
      request_type(const request_type&) = delete;
      request_type(request_type&&) = delete;

      static_assert(!callable_trait<SIGNATURE>::is_variadic, "request does not support variadic arguments");
      using method_type  = ATOM;
      using result_type  = typename callable_trait<SIGNATURE>::result_type;
      using args_type    = typename callable_trait<SIGNATURE>::decayed_args_type;
      using pattern_type = typename callable_trait<SIGNATURE>::decayed_args_type::template prepend_type<ATOM>;
      using msg_type     = typename args_type::template export_to<std::tuple>;
   };
}

#define __CUB_method_name(x)      __MACO_1st   x
#define __CUB_method_signature(x) __MACO_rest  x

////////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_actor_method(n, x)                                           \
struct __CUB_method_name(x);                                               \
template <typename T> struct __SeCrEtE_method<n, T>                        \
   : NANO_CAF_NS::detail::request_type                                     \
           < __CUB_method_name(x), auto __CUB_method_signature(x)> {       \
   constexpr static auto name() -> const char* {                           \
       return __MACO_stringify(__CUB_method_name(x));                       \
   }                                                                       \
};                                                                         \
struct __CUB_method_name(x) : NANO_CAF_NS::atom_signature {                \
   using type = __SeCrEtE_method<n, __SeCrEtE_tHiS_tYpe>;                  \
   struct msg_type : type::msg_type {                                      \
      using tuple_parent = type::msg_type;                                 \
      using tuple_parent::tuple_parent;                                    \
      using result_type = type::result_type;                               \
      constexpr static NANO_CAF_NS::type_id_t type_id =                    \
           static_cast<type_id_t>(n) | __secrete_type_id;                  \
   };                                                                      \
};

///////////////////////////////////////////////////////////////////////////////////////////////
#define __CAF_actor_interface(name, i_type_id, ...)                                      \
struct name {                                                                            \
private:                                                                                 \
   using __SeCrEtE_tHiS_tYpe = name;                                                     \
   static_assert(sizeof(i_type_id) == sizeof(uint32_t) &&                                \
                 std::is_convertible_v<decltype(i_type_id), uint32_t>,                   \
                 "interface type id must be uint32_t");                                  \
   constexpr static NANO_CAF_NS::type_id_t __secrete_type_id =                           \
           static_cast<type_id_t>(i_type_id) << 32;                                      \
public:                                                                                  \
   template <size_t, typename> struct __SeCrEtE_method;                                  \
   constexpr static size_t total_methods = __MACO_pp_size(__VA_ARGS__);                  \
   __MACO_foreach(__CUB_actor_method, __VA_ARGS__);                                      \
}

NANO_CAF_NS_END

#endif //NANO_CAF_REQUEST_H
