//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_BEHAVIOR_H
#define NANO_CAF_BEHAVIOR_H

#include <nano-caf/util/type_list.h>
#include <nano-caf/util/callable_trait.h>
#include <nano-caf/core/msg/message_trait.h>
#include <tuple>
#include <nano-caf/core/msg/message_element.h>
#include "task_list.h"

NANO_CAF_NS_BEGIN

namespace detail {
   template<typename T>
   constexpr bool is_non_const_lref = !std::is_const_v<T> && std::is_lvalue_reference_v<T>;

   template<typename F>
   using first_arg_t = typename callable_trait<F>::template arg<0>;

   template<typename F>
   constexpr bool is_atom = std::is_base_of_v<__atom_signature, std::decay_t<first_arg_t<F>>>;

   template<typename F>
   constexpr bool is_msg_or_atom = std::is_same_v<const msg_id_t, decltype(from_msg_type_to_id<std::decay_t<first_arg_t<F>>>::msg_id)>;

   ////////////////////////////////////////////////////////////////////////////////////////
   template<typename F, typename = void>
   struct verify_behavior_;

   template<typename T>
   struct is_non_rvalue_ref {
      constexpr static bool value = !std::is_rvalue_reference_v<T>;
   };

   template<typename F>
   struct verify_behavior_<F, std::enable_if_t<is_msg_or_atom<F> && is_atom<F>>> {
      static_assert(!is_non_const_lref<first_arg_t<F>>, "the atom type cannot be non-const-lvalue-ref");

      using decayed_args = typename callable_trait<F>::decayed_args_type::tail;
      using args_type = typename callable_trait<F>::args_type::tail;
      using atom_type = std::decay_t<first_arg_t<F>>;
      using message_type = typename from_atom_to_msg_type<atom_type>::type;
      using fields_types = typename from_msg_type_to_field<message_type>::type::tail;
      using decayed_field_types = typename fields_types::template transform<std::decay_t>;

      static_assert(std::is_same_v<decayed_field_types, decayed_args>, "parameters & message don't match");
      static_assert(args_type::template pred<is_non_rvalue_ref>, "parameter cannot be rvalue-ref type");

      struct base {
         base(F&& f) : f_(std::move(f)) {}

         F f_;
      };

      template<size_t N>
      struct ftype;

      template<>
      struct ftype<0>: base {
         using base::base;

         auto operator()(message_element& msg) {
            auto* body = msg.body<message_type>();
            if(body == nullptr) return false;
            base::f_(atom_type{});
            return true;
         }
      };

      template<>
      struct ftype<1>: base {
         using base::base;

         auto operator()(message_element& msg) {
            auto* body = msg.body<message_type>();
            if(body == nullptr) return false;

            auto& [a1] = *body;
            base::f_(atom_type{}, a1);

            return true;
         }
      };

      template<>
      struct ftype<2>: base {
         using base::base;

         auto operator()(message_element& msg) {
            auto* body = msg.body<message_type>();
            if(body == nullptr) return false;

            auto& [a1, a2] = *body;
            base::f_(atom_type{}, a1, a2);

            return true;
         }
      };

      template<>
      struct ftype<3>: base {
         using base::base;

         auto operator()(message_element& msg) {
            auto* body = msg.body<message_type>();
            if(body == nullptr) return false;

            auto& [a1, a2, a3] = *body;
            base::f_(atom_type{}, a1, a2, a3);
            return true;
         }
      };

      template<>
      struct ftype<4>: base {
         using base::base;

         auto operator()(message_element& msg) {
            auto* body = msg.body<message_type>();
            if(body == nullptr) return false;

            auto& [a1, a2, a3, a4] = *body;
            base::f_(atom_type{}, a1, a2, a3, a4);

            return true;
         }
      };

      template<>
      struct ftype<5>: base {
         using base::base;

         auto operator()(message_element& msg) {
            auto* body = msg.body<message_type>();
            if(body == nullptr) return false;

            auto& [a1, a2, a3, a4, a5] = *body;
            base::f_(atom_type{}, a1, a2, a3, a4, a5);

            return true;
         }
      };

      template<>
      struct ftype<6>: base {
         using base::base;

         auto operator()(message_element& msg) {
            auto* body = msg.body<message_type>();
            if(body == nullptr) return false;

            auto& [a1, a2, a3, a4, a5, a6] = *body;
            base::f_(atom_type{}, a1, a2, a3, a4, a5, a6);

            return true;
         }
      };

      template<>
      struct ftype<7>: base {
         using base::base;

         auto operator()(message_element& msg) {
            auto* body = msg.body<message_type>();
            if(body == nullptr) return false;

            auto& [a1, a2, a3, a4, a5, a6, a7] = *body;
            base::f_(atom_type{}, a1, a2, a3, a4, a5, a6, a7);

            return true;
         }
      };

      template<>
      struct ftype<8>: base {
         using base::base;

         auto operator()(message_element& msg) {
            auto* body = msg.body<message_type>();
            if(body == nullptr) return false;

            auto& [a1, a2, a3, a4, a5, a6, a7, a8] = *body;
            base::f_(atom_type{}, a1, a2, a3, a4, a5, a6, a7, a8);
            return true;
         }
      };

      template<>
      struct ftype<9>: base {
         using base::base;

         auto operator()(message_element& msg) {
            auto* body = msg.body<message_type>();
            if(body == nullptr) return false;

            auto& [a1, a2, a3, a4, a5, a6, a7, a8, a9] = *body;
            base::f_(atom_type{}, a1, a2, a3, a4, a5, a6, a7, a8, a9);

            return true;
         }
      };

      using type = ftype<decayed_args::size>;

      constexpr static bool value = true;
   };

   template<typename F>
   struct verify_behavior_<F, std::enable_if_t<is_msg_or_atom<F> && !is_atom<F>>> {
      static_assert((callable_trait<F>::num_of_args == 1), "only message argument is allowed");
      constexpr static bool value = true;

      using message_type = std::decay_t<first_arg_t<F>>;
      static_assert(!std::is_pointer_v<message_type>, "don't use pointer, use reference instead");

      struct type {
         type(F&& f) : f_(std::move(f)) {}

         F f_;

         auto operator()(message_element& msg) -> bool {
            auto* body = msg.body<message_type>();
            if(body == nullptr) return false;
            f_(*body);
            return true;
         }
      };
   };

   template<typename F>
   using verify_behavior = verify_behavior_<F, void>;

   template<typename F>
   using verify_behavior_t = typename verify_behavior<F>::type;

   struct msg_handler {
      virtual auto handle_msg(message_element& msg) -> task_result = 0;
      virtual ~msg_handler() = default;
   };

   template<typename ... Args>
   struct behavior_impl : msg_handler {
      behavior_impl(Args&& ... args) : behaviors_{ std::move(args)...} {}

      std::tuple<Args...> behaviors_;

      auto handle_msg(message_element& msg) -> task_result override {
         return task_result::skip;
      }
   };
}

struct behavior {
   template<typename ... Args>
   behavior(Args&&...args) {
      static_assert(((callable_trait<Args>::num_of_args > 0) && ...));
      static_assert((detail::verify_behavior<Args>::value && ...));
      ptr_ = new detail::behavior_impl{detail::verify_behavior_t<Args>{std::move(args)}...};
   }

   detail::msg_handler* ptr_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_BEHAVIOR_H
