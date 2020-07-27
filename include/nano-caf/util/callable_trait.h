//
// Created by Darwin Yuan on 2020/7/27.
//

#ifndef NANO_CAF_CALLABLE_TRAIT_H
#define NANO_CAF_CALLABLE_TRAIT_H

#include <nano-caf/nano-caf-ns.h>
#include <type_traits>

NANO_CAF_NS_BEGIN

template<typename ... Ts>
struct type_list {};

template<typename T>
struct function_trait;

template<typename R, typename ... Args>
struct function_trait<R (Args...)> {
   using return_type = R;
   using args_type = type_list<Args...>;
   using decayed_args_type = type_list<std::decay_t<Args>...>;
   constexpr static size_t num_of_args = sizeof...(Args);
   constexpr static bool is_variadic = false;
   constexpr static bool is_const = false;
};

template<typename R, typename ... Args>
struct function_trait<R (Args..., ...)> {
   using return_type = R;
   using args_type = type_list<Args...>;
   using decayed_args_type = type_list<std::decay_t<Args>...>;
   constexpr static size_t num_of_args = sizeof...(Args);
   constexpr static bool is_variadic = true;
   constexpr static bool is_const = false;
};

template<typename C, typename R, typename ... Args>
struct function_trait<R (C::*)(Args...) const> {
   using return_type = R;
   using args_type = type_list<Args...>;
   using decayed_args_type = type_list<std::decay_t<Args>...>;
   constexpr static size_t num_of_args = sizeof...(Args);
   constexpr static bool is_variadic = false;
   constexpr static bool is_const = true;
};

template<typename C, typename R, typename ... Args>
struct function_trait<R (C::*)(Args...)> {
   using return_type = R;
   using args_type = type_list<Args...>;
   using decayed_args_type = type_list<std::decay_t<Args>...>;
   constexpr static size_t num_of_args = sizeof...(Args);
   constexpr static bool is_variadic = false;
   constexpr static bool is_const = false;
};

template<typename C, typename R, typename ... Args>
struct function_trait<R (C::*)(Args..., ...)> {
   using return_type = R;
   using args_type = type_list<Args...>;
   using decayed_args_type = type_list<std::decay_t<Args>...>;
   constexpr static size_t num_of_args = sizeof...(Args);
   constexpr static bool is_variadic = true;
   constexpr static bool is_const = false;
};

template<typename C, typename R, typename ... Args>
struct function_trait<R (C::*)(Args..., ...) const> {
   using return_type = R;
   using args_type = type_list<Args...>;
   using decayed_args_type = type_list<std::decay_t<Args>...>;
   constexpr static size_t num_of_args = sizeof...(Args);
   constexpr static bool is_variadic = true;
   constexpr static bool is_const = true;
};

template<typename T, typename = void>
struct callable_trait : function_trait<T> {};

template<typename T>
struct callable_trait<T, std::enable_if_t<std::is_class_v<T>>> : function_trait<decltype(&T::operator())> {};

NANO_CAF_NS_END

#endif //NANO_CAF_CALLABLE_TRAIT_H
