//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_TYPE_LIST_H
#define NANO_CAF_TYPE_LIST_H

#include <nano-caf/nano-caf-ns.h>
#include <cstddef>

NANO_CAF_NS_BEGIN

template<typename ... Ts>
struct type_list {
   constexpr static size_t size = 0;
   template<template<typename T> typename F>
   using transform = type_list<>;

   template<typename T>
   using append_type = type_list<T>;

   template<typename T>
   using prepend_type = type_list<T>;

   template<template<typename ...> typename R>
   using export_to = R<>;
};

template<typename H, typename ... Ts>
struct type_list<H, Ts...> {
   constexpr static size_t size = sizeof...(Ts) + 1;
   using head = H;
   using tail = type_list<Ts...>;

   template<template<typename T> typename F>
   using transform = type_list<F<H>, F<Ts>...>;

   template<template<typename T> typename F>
   constexpr static bool pred = (F<Ts>::value && ... && F<H>::value);

   template<typename T>
   using prepend_type = type_list<T, H, Ts...>;

   template<typename T>
   using append_type = type_list<H, Ts..., T>;

   template<template<typename ...> typename R>
   using export_to = R<H, Ts...>;
};

namespace detail {
   template<typename T, typename ... Ts>
   struct type_list_exists {
      constexpr static bool value = false;
   };

   template<typename T, typename H, typename ... Ts>
   struct type_list_exists<T, H, Ts...> {
      constexpr static bool value = std::is_same_v<T, H> || type_list_exists<T, Ts...>::value;
   };
}

template<typename T, typename TL>
constexpr bool type_list_exists = TL::template prepend_type<T>::template export_to<detail::type_list_exists>::value;

NANO_CAF_NS_END

#endif //NANO_CAF_TYPE_LIST_H
