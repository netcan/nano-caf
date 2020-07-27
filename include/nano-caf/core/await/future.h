//
// Created by Darwin Yuan on 2020/7/27.
//

#ifndef NANO_CAF_FUTURE_H
#define NANO_CAF_FUTURE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/resumable.h>
#include <type_traits>
#include <functional>
#include <optional>
#include <nano-caf/core/actor/message_element.h>

NANO_CAF_NS_BEGIN

struct abstract_future {
   explicit abstract_future(uint8_t index) :index{index} {}
   virtual auto set_value(message_element&) -> void = 0;
   virtual ~abstract_future() = default;

private:
   uint8_t index;
};

template<typename T>
struct future : abstract_future {
   using abstract_future::abstract_future;

   std::optional<T> value{std::nullopt};

private:
   auto set_value(message_element& msg) -> void override {
      this->value = *(msg.body<T>());
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_H
