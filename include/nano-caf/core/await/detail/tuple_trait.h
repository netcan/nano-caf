//
// Created by Darwin Yuan on 2020/9/29.
//

#ifndef NANO_CAF_TUPLE_TRAIT_H
#define NANO_CAF_TUPLE_TRAIT_H

#include <tuple>

#include <nano-caf/core/await/detail/future_object_base.h>

NANO_CAF_NS_BEGIN namespace detail {

template<std::size_t I, typename SEQ, typename ... Xs>
struct filter_out;

template<std::size_t I, std::size_t ...Is, typename H, typename ... Xs>
struct filter_out<I, std::index_sequence<Is...>, H, Xs...> {
   using type = typename filter_out<I+1, std::index_sequence<Is..., I>, Xs...>::type;
};

template<std::size_t I, std::size_t ...Is, typename ... Xs>
struct filter_out<I, std::index_sequence<Is...>, void, Xs...> {
   using type = typename filter_out<I+1, std::index_sequence<Is...>, Xs...>::type;
};

template<std::size_t I, typename SEQ>
struct filter_out<I, SEQ> {
   using type = SEQ;
};

template<typename T>
struct wrapper_t {
   using type = T;
};

template <typename ... Xs>
using tuple_index_t = typename filter_out<0, std::index_sequence<>, Xs...>::type;

template<typename ... Xs, std::size_t ... Is>
auto tuple_trait(std::tuple<Xs...> t, std::index_sequence<Is...>) noexcept ->
std::tuple<std::decay_t<decltype(std::declval<typename std::decay_t<decltype(std::get<Is>(t))>::type>())> ...>;

template<typename ... Xs>
using tuple_trait_t = decltype(tuple_trait(std::tuple<wrapper_t<Xs>...>{}, tuple_index_t<Xs...>{}));

} NANO_CAF_NS_END

#endif //NANO_CAF_TUPLE_TRAIT_H
