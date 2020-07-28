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
};

NANO_CAF_NS_END

#endif //NANO_CAF_TYPE_LIST_H
