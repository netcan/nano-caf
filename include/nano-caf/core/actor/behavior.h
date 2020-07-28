//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_BEHAVIOR_H
#define NANO_CAF_BEHAVIOR_H

#include <nano-caf/util/type_list.h>
#include <nano-caf/util/callable_trait.h>
#include <nano-caf/core/msg/message_trait.h>
#include <tuple>

NANO_CAF_NS_BEGIN

namespace detail {
   template<typename T>
   constexpr bool is_non_const_lref = !std::is_const_v<T> && std::is_lvalue_reference_v<T>;

   template<typename T>
   constexpr bool is_msg_or_atom = std::is_same_v<const msg_id_t, decltype(from_msg_type_to_id<std::decay_t<T>>::msg_id)>;

   template<typename F>
   using first_arg_t = typename callable_trait<F>::template arg<0>;

   ////////////////////////////////////////////////////////////////////////////////////////
   template<typename F, typename = void>
   struct verify_behavior_;

   template<typename T>
   struct is_non_rvalue_ref {
      constexpr static bool value = !std::is_rvalue_reference_v<T>;
   };

   template<typename F>
   struct verify_behavior_<F, std::enable_if_t<std::is_base_of_v<__atom_signature, std::decay_t<first_arg_t<F>>> &&
                                               std::is_same_v<const msg_id_t, decltype(from_msg_type_to_id<std::decay_t<first_arg_t<F>>>::msg_id)>>> {
      static_assert(!is_non_const_lref<first_arg_t<F>>, "the atom type cannot be non-const-lvalue-ref");

      using decayed_args = typename callable_trait<F>::decayed_args_type::tail;
      using args_type = typename callable_trait<F>::args_type::tail;
      using atom_type = std::decay_t<first_arg_t<F>>;
      using message_type = typename from_atom_to_msg_type<atom_type>::type;
      using fields_types = typename from_msg_type_to_field<message_type>::type::tail;
      using decayed_field_types = typename fields_types::template transform<std::decay_t>;
      static_assert(std::is_same_v<decayed_field_types, decayed_args>);
      static_assert(args_type::template pred<is_non_rvalue_ref>, "parameter cannot be rvalue-ref type");

      constexpr static bool value = true;
   };

   template<typename F>
   struct verify_behavior_<F, std::enable_if_t<!std::is_base_of_v<__atom_signature, std::decay_t<first_arg_t<F>>> &&
                                               std::is_same_v<const msg_id_t, decltype(from_msg_type_to_id<std::decay_t<first_arg_t<F>>>::msg_id)>>> {
      static_assert((callable_trait<F>::num_of_args == 1), "only message argument is allowed");
      constexpr static bool value = true;
   };

   template<typename F>
   using verify_behavior = verify_behavior_<F, void>;
}

struct behavior {
   template<typename ... Args>
   behavior(Args&&...args) {
      static_assert(((callable_trait<Args>::num_of_args > 0) && ...));
      static_assert((detail::verify_behavior<Args>::value && ...));
      //std::tuple<std::decay_t<Args>...>{std::forward<Args>(args)...};
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_BEHAVIOR_H
