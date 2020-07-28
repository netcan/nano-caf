//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_TYPE_LIST_H
#define NANO_CAF_TYPE_LIST_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

template<typename ... Ts>
struct type_list {
   template<template<typename T> typename F>
   using transform = type_list<>;
};

template<typename H, typename ... Ts>
struct type_list<H, Ts...> {
   using head = H;
   using tail = type_list<Ts...>;

   template<template<typename T> typename F>
   using transform = type_list<F<H>, F<Ts>...>;
};

NANO_CAF_NS_END

#endif //NANO_CAF_TYPE_LIST_H
