//
// Created by Darwin Yuan on 2020/8/12.
//

#ifndef NANO_CAF_PTR_TRAIT_H
#define NANO_CAF_PTR_TRAIT_H

#include <nano-caf/nano-caf-ns.h>
#include <memory>
#include <type_traits>

NANO_CAF_NS_BEGIN

template<typename T>
struct is_smart_ptr {
   constexpr static bool value = false;
};

template<typename T>
struct is_smart_ptr<std::shared_ptr<T>> {
   constexpr static bool value = true;
};

template<typename T>
struct is_smart_ptr<std::unique_ptr<T>> {
   constexpr static bool value = true;
};

template<typename T>
constexpr bool is_smart_ptr_v = is_smart_ptr<T>::value;

template<typename T>
constexpr bool is_ptr_v = std::is_pointer_v<T> || is_smart_ptr_v<T>;

NANO_CAF_NS_END

#endif //NANO_CAF_PTR_TRAIT_H
