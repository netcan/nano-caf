//
// Created by Darwin Yuan on 2020/8/8.
//

#ifndef NANO_CAF_TYPED_ACTOR_HANDLE_H
#define NANO_CAF_TYPED_ACTOR_HANDLE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/atom.h>
#include <nano-caf/util/macro_basic.h>
#include <nano-caf/util/macro_pp_size.h>
#include <nano-caf/util/macro_reflex_call.h>
#include <nano-caf/util/callable_trait.h>
#include <nano-caf/util/type_list.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <optional>
#include <utility>
#include <nano-caf/util/either.h>
#include <nano-caf/util/status_t.h>
#include <nano-caf/util/result_trait.h>

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
struct typed_actor_handle : private actor_handle {
   typed_actor_handle(intrusive_actor_ptr ptr = nullptr) : actor_handle{ptr} {}

   using actor_handle::wait_for_exit;
   using actor_handle::release;
   using actor_handle::exit;

   template<typename METHOD_ATOM, typename ... Args,
      typename = std::enable_if_t<detail::is_msg_valid<METHOD_ATOM, ACTOR_INTERFACE, Args...>>>
   auto send(METHOD_ATOM atom, Args&& ... args) {
      return actor_handle::send<typename METHOD_ATOM::msg_type>(std::forward<Args>(args)...);
   }

private:
   template<typename T>
   struct promised_request_handler : request_result_handler<T> {
      auto handle(const T& value) -> void override {
         promise_.set_value(value);
         value_set_ = true;
      }

      promised_request_handler() = default;
      promised_request_handler(promised_request_handler&& handler)
         : promise_{std::move(handler.promise_)}
         , value_set_{handler.value_set_} {
         handler.value_set_ = true;
      }

      ~promised_request_handler() {
         if(!value_set_) promise_.set_value(status_t::failed);
      }

      std::promise<either<T, status_t>> promise_{};
      bool value_set_{false};
   };

   template<typename T>
   struct inter_actor_promise_handler : promised_request_handler<T> {
      inter_actor_promise_handler(intrusive_actor_ptr sender)
         : sender_{sender}
      {}

      auto handle(const T& value) -> void override {
         promised_request_handler<T>::handle(value);
         sender_.send<future_done, (message::category)message::future>();
      }

      actor_handle sender_;
   };

   template<typename T, typename H_SUCC>
   struct delegate_request_handler : request_result_handler<T> {
      delegate_request_handler(H_SUCC&& h_succ)
         : h_succ_{std::move(h_succ)}
      {}

      static_assert(std::is_invocable_r_v<void, H_SUCC, T>, "T function signature mismatch");

      auto handle(const T& value) -> void override {
         h_succ_(value);
      }

      H_SUCC h_succ_;
   };

   template<typename METHOD_ATOM, typename F>
   struct request_rsp_base {
      request_rsp_base(F&& f) : f_{std::move(f)} {}

      F f_;
   };

   template<typename METHOD_ATOM, typename F>
   struct wait_rsp : protected request_rsp_base<METHOD_ATOM, F> {
   protected:
      using base = request_rsp_base<METHOD_ATOM, F>;
      using result_type = result_t<typename METHOD_ATOM::type::result_type>;

   public:
      using base::base;

      using wait_result_t = either<result_type, status_t>;
   private:
      template<typename F_WAIT>
      auto wait_(F_WAIT&& f_wait) -> wait_result_t {
         auto handler = promised_request_handler<result_type>{};
         auto future = handler.promise_.get_future();

         if(base::f_(handler) != enq_result::ok) {
            return status_t::failed;
         }

         auto status = f_wait(future);
         if(status != std::future_status::ready) {
            return status_t::timeout;
         }

         return future.get();
      }

   public:
      auto wait(const std::chrono::microseconds& duration) -> wait_result_t {
         return wait_([&](auto& future){ return future.wait_for(duration); });
      }

      auto wait() -> wait_result_t {
         return wait_([&](auto& future){ return std::future_status::ready; });
      }
   };

   template<typename METHOD_ATOM, typename F>
   struct then_rsp : wait_rsp<METHOD_ATOM, F> {
   private:
      using base = wait_rsp<METHOD_ATOM, F>;
      using result_type = result_t<typename METHOD_ATOM::type::result_type>;

   public:
      using base::base;

      template<typename H_SUCC, typename H_FAIL>
      auto then(H_SUCC&& h_succ, H_FAIL&& h_fail) {
         if(base::f_(
            delegate_request_handler<result_type, H_SUCC>
               { std::forward<H_SUCC>(h_succ) }) != enq_result::ok) {
            h_fail(status_t::failed);
         }
      }
   };

public:
   template<typename METHOD_ATOM, typename ... Args,
      typename = std::enable_if_t<detail::is_msg_valid<METHOD_ATOM, ACTOR_INTERFACE, Args...>>>
   auto request(METHOD_ATOM atom, Args&& ... args) {
      auto l = [&, this](auto&& handler) {
         return actor_handle::request<typename METHOD_ATOM::msg_type>(
               std::forward<decltype(handler)>(handler),
               std::forward<Args>(args)...);
      };
      return then_rsp<METHOD_ATOM, decltype(l)>(std::move(l));
   }
   template<typename METHOD_ATOM>
   using future_type = std::future<either<result_t<typename METHOD_ATOM::type::result_type>, status_t>>;

   template<typename METHOD_ATOM, typename ... Args,
      typename = std::enable_if_t<detail::is_msg_valid<METHOD_ATOM, ACTOR_INTERFACE, Args...>>>
   auto request(intrusive_actor_ptr from, METHOD_ATOM atom, Args&& ... args)
      -> either<future_type<METHOD_ATOM>, status_t> {
      using result_type = result_t<typename METHOD_ATOM::type::result_type>;
      inter_actor_promise_handler<result_type> promise{ from };
      auto future = promise.promise_.get_future();
      auto result = actor_handle::request<typename METHOD_ATOM::msg_type>(
         from,
         promise,
         std::forward<Args>(args)...);
      if(result != enq_result::ok) {
         return status_t::failed;
      }

      return future;
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_TYPED_ACTOR_HANDLE_H
