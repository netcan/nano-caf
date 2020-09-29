//
// Created by Darwin Yuan on 2020/9/29.
//

#ifndef NANO_CAF_FUTURE_TRAIT_H
#define NANO_CAF_FUTURE_TRAIT_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

template<typename T>
struct future;

namespace detail {
   template<typename T>
   struct future_trait;

   template<typename T>
   struct future_trait<future<T>> { using type = T; };

   template<typename T>
   using future_trait_t = typename future_trait<T>::type;
}

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_TRAIT_H
