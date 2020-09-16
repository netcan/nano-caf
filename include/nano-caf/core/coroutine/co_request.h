//
// Created by Darwin Yuan on 2020/9/16.
//

#ifndef NANO_CAF_CO_REQUEST_H
#define NANO_CAF_CO_REQUEST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/request_reply.h>
#include <coroutine>

NANO_CAF_NS_BEGIN

template<typename METHOD_ATOM, message::category CATEGORY = message::normal>
struct request {
   using result_type = requester::method_result_t<METHOD_ATOM>;
   using message_type = typename METHOD_ATOM::msg_type;

   template<typename ... Args>
   request(intrusive_actor_ptr to, Args&& ... args)
      : to_{std::move(to)}
      , message_{std::forward<Args>(args)...}
   {}

   template<typename A, typename ... Args>
   request(typed_actor_handle<A> to, Args&& ... args)
      : to_{std::move(to.get())}
      , message_{std::forward<Args>(args)...}
   {}

   auto await_ready() const noexcept { return false; }

   template<typename P>
   auto await_suspend(std::coroutine_handle<P> caller) noexcept -> bool {
      auto* actor = &caller.promise().get_actor();
      auto status = actor_handle(to_).request<typename METHOD_ATOM::msg_type, CATEGORY>
         ( caller.promise().get_self_handle()
         , requester::make_delegate_request_handler<METHOD_ATOM>([=, this](auto&& result) {
            if(actor->coroutine_alive(caller)) {
               result_ = std::move(result);
               caller();
            }
         })
         , std::move(message_));
      if(status == status_t::ok) {
         return true;
      }

      result_ = status;
      return false;
   }

   auto await_resume() const noexcept {
      return result_;
   };

private:
   intrusive_actor_ptr to_;
   message_type message_;
   result_type result_{status_t::failed};
};

NANO_CAF_NS_END

#endif //NANO_CAF_CO_REQUEST_H
