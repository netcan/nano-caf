//
// Created by Darwin Yuan on 2020/8/23.
//

#ifndef NANO_CAF_TIMER_CALLBACK_H
#define NANO_CAF_TIMER_CALLBACK_H

#include <nano-caf/nano-caf-ns.h>
#include <utility>

NANO_CAF_NS_BEGIN

struct timer_callback {
   virtual auto on_timeout() noexcept -> void = 0;
   virtual ~timer_callback() = default;
};

template<typename F>
struct generic_timer_callback : timer_callback {
   generic_timer_callback(F&& f) : f_(std::move(f)) {}
   auto on_timeout() noexcept -> void override {
      f_();
   }
private:
   F f_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_TIMER_CALLBACK_H
