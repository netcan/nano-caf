//
// Created by Darwin Yuan on 2020/8/10.
//

#ifndef NANO_CAF_REQUESTER_H
#define NANO_CAF_REQUESTER_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/atom.h>
#include <nano-caf/util/callable_trait.h>
#include <nano-caf/util/type_list.h>
#include <nano-caf/util/either.h>
#include <nano-caf/util/status_t.h>
#include <nano-caf/util/result_trait.h>
#include <nano-caf/core/msg/request_result_handler.h>
#include <nano-caf/core/actor/intrusive_actor_ptr.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <optional>
#include <utility>
#include <future>

NANO_CAF_NS_BEGIN namespace requester {

template<typename T, size_t ... I>
auto deduce_method_atoms(std::index_sequence<I...>)
-> type_list<typename T::template __SeCrEtE_method<I, T>::method_type...>;

template<typename T>
using method_atoms = decltype(deduce_method_atoms<T>(std::make_index_sequence<T::total_methods>{}));

template<typename T, size_t ... I>
auto deduce_method_pattens(std::index_sequence<I...>) -> type_list<typename T::template __SeCrEtE_method<I, T>::pattern_type...>;

template<typename T>
using method_pattens = decltype(deduce_method_pattens<T>(std::make_index_sequence<T::total_methods>{}));

template<typename METHOD_ATOM, typename ACTOR_INTERFACE, typename ...Args>
constexpr bool msg_pattern_match =
   type_exists<NANO_CAF_NS::type_list<METHOD_ATOM, std::decay_t<Args>...>, NANO_CAF_NS::requester::method_pattens<ACTOR_INTERFACE>>;

template<typename METHOD_ATOM, typename ACTOR_INTERFACE, typename ...Args>
constexpr bool is_msg_valid = is_msg_atom<METHOD_ATOM> && msg_pattern_match<METHOD_ATOM, ACTOR_INTERFACE, Args...>;

template<typename METHOD_ATOM>
using result_type = result_t<typename METHOD_ATOM::type::result_type>;

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
      sender_.send<future_done, static_cast<message::category>(message::future)>();
   }

   actor_handle sender_;
};

template<typename T, typename H_RESULT>
struct delegate_request_handler : request_result_handler<T> {
   delegate_request_handler(H_RESULT&& h_result)
      : h_result_{std::move(h_result)}
   {}

   static_assert(std::is_invocable_r_v<void, H_RESULT, T>, "T function signature mismatch");

   auto handle(const T& value) -> void override {
      h_result_(value);
   }

   H_RESULT h_result_;
};


template<typename METHOD_ATOM, typename F>
struct request_rsp_base {
   request_rsp_base(F&& f) : f_{std::move(f)} {}


   template<typename HANDLER>
   auto invoke(HANDLER&& handler) {
      invoked_ = true;
      return f_(std::forward<HANDLER>(handler));
   }

   struct dummy_request_handler : request_result_handler<result_type<METHOD_ATOM>> {
      auto handle(const result_type<METHOD_ATOM>&) -> void override {}
   };

   ~request_rsp_base() {
      if(!invoked_) {
         if(auto status = f_(dummy_request_handler{}); status != status_t::ok) {
            // error log
         }
      };
   }
private:
   F f_;
   bool invoked_{false};
};

template<typename METHOD_ATOM, typename F>
struct wait_rsp : protected request_rsp_base<METHOD_ATOM, F> {
protected:
   using base = request_rsp_base<METHOD_ATOM, F>;

public:
   using base::base;

   using wait_result_t = either<result_type<METHOD_ATOM>, status_t>;
private:
   template<typename F_WAIT>
   auto wait_(F_WAIT&& f_wait) -> wait_result_t {
      auto handler = promised_request_handler<result_type<METHOD_ATOM>>{};
      auto future = handler.promise_.get_future();

      if(auto status = base::invoke(handler); status != status_t::ok) {
         return status;
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
      return wait_([&](auto&){ return std::future_status::ready; });
   }
};

template<typename METHOD_ATOM, typename F>
struct [[nodiscard]] then_rsp : wait_rsp<METHOD_ATOM, F> {
private:
   using base = wait_rsp<METHOD_ATOM, F>;

public:
   using base::base;

   template<typename H_RESULT, typename H_FAIL>
   auto then(H_RESULT&& h_result, H_FAIL&& h_fail) {
      delegate_request_handler<result_type<METHOD_ATOM>, H_RESULT> handler{ std::forward<H_RESULT>(h_result) };
      if(auto status = base::invoke(std::move(handler)); status != status_t::ok) {
         h_fail(status);
      }
   }
};

template<typename METHOD_ATOM>
using method_result_t = either<result_type<METHOD_ATOM>, status_t>;

template<typename METHOD_ATOM>
using future_type = std::future<method_result_t<METHOD_ATOM>>;

} NANO_CAF_NS_END

#endif //NANO_CAF_REQUESTER_H
