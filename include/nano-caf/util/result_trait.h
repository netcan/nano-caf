//
// Created by Darwin Yuan on 2020/8/9.
//

#ifndef NANO_CAF_RESULT_TRAIT_H
#define NANO_CAF_RESULT_TRAIT_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/unit.h>

NANO_CAF_NS_BEGIN

namespace detail {
   template<typename T>
   struct result_trait {
      using type = T;
   };

   template<>
   struct result_trait<void> {
      using type = unit_t;
   };
}

template<typename T>
using func_result_t = typename detail::result_trait<T>::type;

NANO_CAF_NS_END

#endif //NANO_CAF_RESULT_TRAIT_H
