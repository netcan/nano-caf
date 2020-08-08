//
// Created by Darwin Yuan on 2020/8/8.
//

#ifndef NANO_CAF_TYPE_ACTOR_HANDLE_H
#define NANO_CAF_TYPE_ACTOR_HANDLE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/atom.h>
#include <nano-caf/util/macro_basic.h>
#include <nano-caf/util/macro_pp_size.h>
#include <nano-caf/util/macro_reflex_call.h>
#include <nano-caf/util/callable_trait.h>
#include <nano-caf/util/type_list.h>
#include <utility>
#include "actor_handle.h"

NANO_CAF_NS_BEGIN

namespace detail {
   template<typename T, size_t ... I>
   auto deduce_method_atoms(std::index_sequence<I...>)
   -> type_list<typename T::template __SeCrEtE_method<I, T>::method_type...>;

   template<typename T>
   using method_atoms = decltype(detail::deduce_method_atoms<T>(std::make_index_sequence<T::total_methods>{}));

   template<typename T, size_t ... I>
   auto deduce_method_pattens(std::index_sequence<I...>)
   -> type_list<typename T::template __SeCrEtE_method<I, T>::pattern_type...>;

   template<typename T>
   using method_pattens = decltype(detail::deduce_method_pattens<T>(std::make_index_sequence<T::total_methods>{}));
}

namespace detail {
   template<typename METHOD_ATOM, typename ACTOR_INTERFACE, typename ...Args>
   constexpr bool msg_pattern_match =
      type_exists<NANO_CAF_NS::type_list<METHOD_ATOM, std::decay_t<Args>...>, NANO_CAF_NS::detail::method_pattens<ACTOR_INTERFACE>>;

   template<typename METHOD_ATOM, typename ACTOR_INTERFACE, typename ...Args>
   constexpr bool is_msg_valid = is_msg_atom<METHOD_ATOM> && msg_pattern_match<METHOD_ATOM, ACTOR_INTERFACE, Args...>;
}

template<typename ACTOR_INTERFACE>
struct type_actor_handle : private actor_handle {
   type_actor_handle(intrusive_actor_ptr ptr) : actor_handle{ptr} {}

   using actor_handle::wait_for_exit;
   using actor_handle::release;
   using actor_handle::exit;

   template<typename METHOD_ATOM, typename ... Args,
      typename = std::enable_if_t<detail::is_msg_valid<METHOD_ATOM, ACTOR_INTERFACE, Args...>>>
   auto send(METHOD_ATOM atom, Args&& ... args) {
      return actor_handle::send<typename METHOD_ATOM::msg_type>(std::forward<Args>(args)...);
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_TYPE_ACTOR_HANDLE_H
