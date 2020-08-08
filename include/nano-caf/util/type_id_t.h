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
      constexpr static int id{0};
   };
}

using type_id_t = const int*;

template<typename T, typename ... Ts>
constexpr type_id_t type_id = &detail::type_id_holder<T, Ts...>::id;

NANO_CAF_NS_END

#endif //NANO_CAF_TYPE_ID_T_H
