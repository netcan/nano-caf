//
// Created by Darwin Yuan on 2020/9/16.
//

#ifndef NANO_CAF_REQUEST_REPLY_H
#define NANO_CAF_REQUEST_REPLY_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/predefined-msgs.h>
#include <nano-caf/core/actor/actor_handle.h>

NANO_CAF_NS_BEGIN namespace requester {

template<typename CALLBACK, typename R>
struct reply_done_notifier : promise_done_notifier {
   reply_done_notifier(CALLBACK &&callback, R &&result)
      : callback_{std::move(callback)}, result_{std::move(result)} {}

   auto on_promise_done() noexcept -> void override {
      callback_(std::move(result_));
   }

   CALLBACK callback_;
   R result_;
};

template<typename R, typename CALLBACK>
struct delegate_request_handler : abstract_promise<R> {
   delegate_request_handler(CALLBACK&& callback)
      : callback_{std::move(callback)} {}

   static_assert(std::is_invocable_r_v < void, CALLBACK, R > , "R function signature mismatch");

   auto set_value(R &&value, intrusive_actor_ptr &sender) noexcept -> void override {
      if (static_cast<bool>(sender)) {
         actor_handle{sender}.send<reply_msg>(
            std::unique_ptr<promise_done_notifier>(new reply_done_notifier{std::move(callback_), std::move(value)}));
      } else {
         callback_(std::move(value));
      }
   }

   CALLBACK callback_;
};

template<typename METHOD_ATOM>
using result_type = func_result_t<typename METHOD_ATOM::type::result_type>;

template<typename METHOD_ATOM>
using method_result_t = result_t<result_type<METHOD_ATOM>>;

template<typename METHOD_ATOM, typename CALLBACK>
auto make_delegate_request_handler(CALLBACK&& f) {
   return delegate_request_handler<result_type<METHOD_ATOM>, std::decay_t<CALLBACK>>{std::forward<CALLBACK>(f)};
}

} NANO_CAF_NS_END

#endif //NANO_CAF_REQUEST_REPLY_H
