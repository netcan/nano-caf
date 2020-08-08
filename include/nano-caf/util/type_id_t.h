//
// Created by Darwin Yuan on 2020/8/8.
//

#ifndef NANO_CAF_TYPE_ID_T_H
#define NANO_CAF_TYPE_ID_T_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

namespace detail {
   template<typename T, typename ... Ts>
   struct type_id_holder {
      alignas(1) constexpr static char id[1]{};
   };
}

using type_id_t = const char*;

template<typename T, typename ... Ts>
constexpr type_id_t type_id = detail::type_id_holder<T, Ts...>::id;

NANO_CAF_NS_END

#endif //NANO_CAF_TYPE_ID_T_H
