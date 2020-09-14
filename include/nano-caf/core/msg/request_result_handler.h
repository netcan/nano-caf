//
// Created by Darwin Yuan on 2020/8/10.
//

#ifndef NANO_CAF_REQUEST_RESULT_HANDLER_H
#define NANO_CAF_REQUEST_RESULT_HANDLER_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/intrusive_actor_ptr.h>

NANO_CAF_NS_BEGIN

template<typename T>
struct request_result_handler {
   virtual auto handle(T&&, intrusive_actor_ptr&) -> void = 0;
   virtual ~request_result_handler() = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_REQUEST_RESULT_HANDLER_H
