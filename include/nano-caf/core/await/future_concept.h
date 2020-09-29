//
// Created by Darwin Yuan on 2020/9/30.
//

#ifndef NANO_CAF_FUTURE_CONCEPT_H
#define NANO_CAF_FUTURE_CONCEPT_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

template<typename T>
struct future;

template<typename T>
constexpr bool Is_Future = false;

template<typename T>
constexpr bool Is_Future<future<T>> = true;

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_CONCEPT_H
