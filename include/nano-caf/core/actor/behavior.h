//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_BEHAVIOR_H
#define NANO_CAF_BEHAVIOR_H

#include <nano-caf/util/type_list.h>
#include <nano-caf/util/callable_trait.h>
#include <nano-caf/core/msg/message_trait.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/task_result.h>
#include <nano-caf/util/aggregate_reflex.h>
#include <tuple>
#include <iostream>
#include <nano-caf/util/unit.h>

NANO_CAF_NS_BEGIN

namespace detail {
   template<typename T>
   constexpr bool is_non_const_lref = !std::is_const_v<T> && std::is_lvalue_reference_v<T>;

   template<typename F>
   using first_arg_t = typename callable_trait<F>::template arg<0>;

   template<typename F>
   constexpr bool is_atom = is_msg_atom<std::decay_t<first_arg_t<F>>>;

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

      using result_type = typename callable_trait<F>::result_type;

      auto handle_msg(message &msg, auto (*handler)(const MSG_TYPE& msg, F& f) -> result_type) -> bool {
         auto *body = msg.body<MSG_TYPE>();
         if (body == nullptr) return false;
         if constexpr(std::is_same_v<void, result_type>) {
            handler(*body, f_);
            auto callback = msg.get_request_result_handler<unit_t>();
            if(callback != nullptr) {
               callback->handle(unit);
            }
         } else {
            auto result = handler(*body, f_);
            auto callback = msg.get_request_result_handler<result_type>();
            if(callback != nullptr) {
               callback->handle(result);
            }
         }

         return true;
      }
   };

   template<typename F, typename = void>
   struct behavior_trait;

   template <typename> struct is_tuple: std::false_type {};
   template <typename ...T> struct is_tuple<std::tuple<T...>>: std::true_type {};

   template <typename ... Ts>
   auto deduce_tuple_types(std::tuple<Ts...>) -> type_list<Ts...>;

   template <typename T, typename = void>
   struct msg_type_trait;

   template <typename T>
   struct msg_type_trait<T, std::enable_if_t<std::is_aggregate_v<T>>> : aggregate_trait<T> {
      using result_type = void;
   };

   template <typename T>
   struct msg_type_trait<T, std::enable_if_t<is_tuple<typename T::tuple_parent>::value>>  {
      using fields_types = decltype(deduce_tuple_types(std::declval<T>()));
      using result_type = typename T::result_type;
      template <typename F>
      static auto call(const T& obj, F&& f) {
         return detail::aggregate_fields_type<fields_types::size, typename T::tuple_parent>::call(
            static_cast<const typename T::tuple_parent&>(obj), std::forward<F>(f));
      }
   };

   template <typename T> struct S;

   template<typename F>
   struct behavior_trait<F, std::enable_if_t<is_atom<F>>> {
      static_assert(!is_non_const_lref<first_arg_t<F>>, "the atom type cannot be non-const-lvalue-ref");
      using atom_type = std::decay_t<first_arg_t<F>>;
      using message_type = typename atom_type::msg_type;
      using fields_types = typename msg_type_trait<message_type>::fields_types;
      template <typename ... Ts>
      using invokable = std::is_invocable<F, atom_type, std::decay_t<Ts>...>;

      static_assert(fields_types::template export_to<invokable>::value, "parameters & message don't match");

      template <typename ... Ts>
      using invoke_result = std::invoke_result_t<F, atom_type, Ts...>;
      using invoke_result_t = typename fields_types::template export_to<invoke_result>;

      static_assert(std::is_same_v<invoke_result_t, typename msg_type_trait<message_type>::result_type>, "return type mismatch");

      using base = behavior_base<F, message_type>;
      struct type : base {
         using base::base;
         auto operator()(message &msg) {
            return base::handle_msg(msg, [](const message_type& msg, F& f) -> invoke_result_t {
               return msg_type_trait<message_type>::call(msg, [&](auto &&... args) -> invoke_result_t {
                  return f(atom_type{}, std::forward<decltype(args)>(args)...);
               });
            });
         }
      };
   };

   template<typename F>
   struct behavior_trait<F, std::enable_if_t<!is_atom<F>>> {
      static_assert((callable_trait<F>::num_of_args == 1), "only message argument is allowed");
      using message_type = std::decay_t<first_arg_t<F>>;
      static_assert(!std::is_pointer_v<message_type>, "don't use pointer, use reference instead");

      using base = behavior_base<F, message_type>;
      struct type : base {
         using base::base;
         auto operator()(message &msg) -> bool {
            return base::handle_msg(msg, [](const message_type& msg, F& f) { return f(msg); });
         }
      };
   };

   template<typename F>
   using behavior_t = typename behavior_trait<F>::type;
}

/////////////////////////////////////////////////////////////////////////////////////
namespace detail {
   struct msg_handler {
      virtual auto handle_msg(message& msg) -> task_result = 0;
      virtual ~msg_handler() = default;
   };

   template<typename ... Args>
   struct behaviors : msg_handler {
      behaviors(Args&& ... args) : behaviors_{std::move(args)...} {}
      auto handle_msg(message& msg) -> task_result override {
         return handle(msg, std::make_index_sequence<sizeof...(Args)>{}) ?
                task_result::resume : task_result::skip;
      }

   private:
      template<size_t ... I>
      auto handle(message& msg, std::index_sequence<I...>) -> bool {
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
