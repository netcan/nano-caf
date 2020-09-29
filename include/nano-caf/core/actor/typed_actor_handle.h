//
// Created by Darwin Yuan on 2020/8/8.
//

#ifndef NANO_CAF_TYPED_ACTOR_HANDLE_H
#define NANO_CAF_TYPED_ACTOR_HANDLE_H

#include <nano-caf/core/actor/requester.h>
#include <nano-caf/core/await/promise.h>

NANO_CAF_NS_BEGIN

template<typename ACTOR_INTERFACE>
struct typed_actor_handle : private actor_handle {
   typed_actor_handle(intrusive_actor_ptr ptr = nullptr) : actor_handle{ptr} {}

   using actor_handle::wait_for_exit;
   using actor_handle::release;
   using actor_handle::exit;
   using actor_handle::get;

   template<typename METHOD_ATOM, message::category CATEGORY = message::normal, typename ... Args,
      typename = std::enable_if_t<requester::is_msg_valid<METHOD_ATOM, ACTOR_INTERFACE, Args...>>>
   auto send(Args&& ... args) {
      return actor_handle::send<typename METHOD_ATOM::msg_type, CATEGORY>(std::forward<Args>(args)...);
   }

   template<typename METHOD_ATOM, message::category CATEGORY = message::normal, typename ... Args,
      typename = std::enable_if_t<requester::is_msg_valid<METHOD_ATOM, ACTOR_INTERFACE, Args...>>>
   auto send(intrusive_actor_ptr sender, Args&& ... args) {
      return actor_handle::send<typename METHOD_ATOM::msg_type, CATEGORY>(sender, std::forward<Args>(args)...);
   }

   template<typename METHOD_ATOM, message::category CATEGORY = message::normal, typename ... Args,
      typename = std::enable_if_t<requester::is_msg_valid<METHOD_ATOM, ACTOR_INTERFACE, Args...>>>
   auto request(Args&& ... args) {
      auto l = [&](auto&& handler) mutable {
         return actor_handle::request<typename METHOD_ATOM::msg_type, CATEGORY>(
               std::forward<decltype(handler)>(handler),
               std::forward<Args>(args)...);
      };
      return requester::then_rsp<METHOD_ATOM, decltype(l), requester::wait_rsp>(std::move(l));
   }

   template<typename METHOD_ATOM, message::category CATEGORY = message::normal, typename ... Args,
      typename = std::enable_if_t<requester::is_msg_valid<METHOD_ATOM, ACTOR_INTERFACE, Args...>>>
   auto request(on_actor_context& context, intrusive_actor_ptr from, Args&& ... args) {
      using result_type = typename METHOD_ATOM::msg_type::result_type;
      promise<result_type> p;
      auto f = p.get_future(context);
      auto result = actor_handle::request<typename METHOD_ATOM::msg_type, CATEGORY>(
            from,
            std::move(p),
            std::forward<Args>(args)...);
      if(result != status_t::ok) {
         return future<result_type>{};
      }

      return f;


//      context, [=, args = std::make_tuple(std::forward<Args>(args) ...)]
//         (detail::future_object_sp<result_type> obj) mutable {
//         return actor_handle::request<typename METHOD_ATOM::msg_type, CATEGORY>(
//            from,
//            promise<result_type>{obj},
//            std::move(args));
//      }
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_TYPED_ACTOR_HANDLE_H
