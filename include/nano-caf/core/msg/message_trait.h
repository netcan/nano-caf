//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_MESSAGE_TRAIT_H
#define NANO_CAF_MESSAGE_TRAIT_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/type_list.h>
#include <nano-caf/util/macro_reflex.h>
#include <cstdint>
#include <utility>

NANO_CAF_NS_BEGIN

using msg_id_t = uint64_t;
struct __atom_signature {};

namespace detail {
   template<typename T, size_t ... I>
   auto deduce_msg_arg_types(std::index_sequence<I...>)
   -> type_list<typename T::template __SeCrEtE_field<I, T>::type...>;
}

#define __CAF_def_message(name, id, ...) \
struct name { \
   __CUB_fields(__VA_ARGS__) \
   constexpr static msg_id_t msg_id = id;  \
   using fIeLd_TyPeS = decltype(detail::deduce_msg_arg_types<name>(std::make_index_sequence<name::NuM_oF_fIeLdS>{})); \
}; \
struct name##_atom : __atom_signature { using msg_type = name; constexpr static msg_id_t msg_id = name::msg_id; }


///////////////////////////////////////////////////////////////////////////////////////////////
#define CAF_def_message(name, ...) __CAF_def_message(name, __COUNTER__, ##__VA_ARGS__)

NANO_CAF_NS_END

#endif //NANO_CAF_MESSAGE_TRAIT_H
