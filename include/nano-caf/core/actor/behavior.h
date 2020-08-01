//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_BEHAVIOR_H
#define NANO_CAF_BEHAVIOR_H

#include <nano-caf/util/type_list.h>
#include <nano-caf/util/callable_trait.h>
#include <nano-caf/core/msg/message_trait.h>
#include <nano-caf/core/msg/message_element.h>
#include <nano-caf/core/actor/task_list.h>
#include <nano-caf/util/aggregate_reflex.h>
#include <tuple>

NANO_CAF_NS_BEGIN

namespace detail {
   template<typename T>
   constexpr bool is_non_const_lref = !std::is_const_v<T> && std::is_lvalue_reference_v<T>;

   template<typename F>
   using first_arg_t = typename callable_trait<F>::template arg<0>;

   template<typename F>
   constexpr bool is_atom = is_msg_atom<std::decay_t<first_arg_t<F>>>;

   template<typename F>
   constexpr bool is_msg_or_atom = std::is_same_v<const msg_id_t, decltype(std::decay_t<first_arg_t<F>>::msg_id)>;

   template<typename T>
   struct is_non_rvalue_ref {
      constexpr static bool value = !std::is_rvalue_reference_v<T>;
   };
}

////////////////////////////////////////////////////////////////////////////////////////
namespace detail {
   template<typename F, typename MSG_TYPE>
   struct behavior_base {
      behavior_base(F &&f) : f_(std::move(f)) {}
      F f_;

      auto handle_msg(message_element &msg, void (*handler)(const MSG_TYPE& msg, F& f)) -> bool {
         auto *body = msg.body<MSG_TYPE>();
         if (body == nullptr) return false;
         handler(*body, f_);
         return true;
      }
   };

   template<typename F, typename = void>
   struct behavior_trait;

   template<typename F>
   struct behavior_trait<F, std::enable_if_t<is_msg_or_atom<F> && is_atom<F>>> {
      static_assert(!is_non_const_lref<first_arg_t<F>>, "the atom type cannot be non-const-lvalue-ref");

      using decayed_args = typename callable_trait<F>::decayed_args_type::tail;
      using args_type = typename callable_trait<F>::args_type::tail;
      using atom_type = std::decay_t<first_arg_t<F>>;
      using message_type = typename atom_type::msg_type;
      using fields_types = typename aggregate_trait<message_type>::fields_type;
      using decayed_field_types = typename fields_types::template transform<std::decay_t>;

      static_assert(std::is_same_v<decayed_field_types, decayed_args>, "parameters & message don't match");
      static_assert(args_type::template pred<is_non_rvalue_ref>, "parameter cannot be rvalue-ref type");

      using base = behavior_base<F, message_type>;
      struct type : base {
         using base::base;
         auto operator()(message_element &msg) {
            return base::handle_msg(msg, [](const message_type& msg, F& f) {
               aggregate_trait<message_type>::call(msg, [&](auto &&... args) {
                  f(atom_type{}, std::forward<decltype(args)>(args)...);
               });
            });
         }
      };
   };

   template<typename F>
   struct behavior_trait<F, std::enable_if_t<is_msg_or_atom<F> && !is_atom<F>>> {
      static_assert((callable_trait<F>::num_of_args == 1), "only message argument is allowed");
      using message_type = std::decay_t<first_arg_t<F>>;
      static_assert(!std::is_pointer_v<message_type>, "don't use pointer, use reference instead");

      using base = behavior_base<F, message_type>;
      struct type : base {
         using base::base;
         auto operator()(message_element &msg) -> bool {
            return base::handle_msg(msg, [](const message_type& msg, F& f) { f(msg); });
         }
      };
   };

   template<typename F>
   using behavior_t = typename behavior_trait<F>::type;
}

/////////////////////////////////////////////////////////////////////////////////////
namespace detail {
   struct msg_handler {
      virtual auto handle_msg(message_element& msg) -> task_result = 0;
      virtual ~msg_handler() = default;
   };

   template<typename ... Args>
   struct behaviors : msg_handler {
      behaviors(Args&& ... args) : behaviors_{std::move(args)...} {}
      auto handle_msg(message_element& msg) -> task_result override {
         return handle(msg, std::make_index_sequence<sizeof...(Args)>{}) ?
                task_result::resume : task_result::skip;
      }

   private:
      template<size_t ... I>
      auto handle(message_element& msg, std::index_sequence<I...>) -> bool {
         return (std::get<I>(behaviors_)(msg) || ...);
      }

      std::tuple<Args...> behaviors_;
   };
}

/////////////////////////////////////////////////////////////////////////////////////
struct behavior {
   template<typename ... Args>
   behavior(Args&&...args) {
      static_assert(((callable_trait<Args>::num_of_args > 0) && ...));
      ptr_.reset(new detail::behaviors{detail::behavior_t<Args>{std::move(args)}...});
   }

   std::unique_ptr<detail::msg_handler> ptr_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_BEHAVIOR_H
