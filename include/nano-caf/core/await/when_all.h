//
// Created by Darwin Yuan on 2020/9/29.
//

#ifndef NANO_CAF_WHEN_ALL_H
#define NANO_CAF_WHEN_ALL_H

#include <nano-caf/core/await/future.h>

NANO_CAF_NS_BEGIN

template<typename ... Xs>
auto when_all(on_actor_context& context, future<Xs>& ... futures) noexcept {
   return future<detail::tuple_trait_t<Xs...>>(context, futures...);
}

NANO_CAF_NS_END

#endif //NANO_CAF_WHEN_ALL_H
