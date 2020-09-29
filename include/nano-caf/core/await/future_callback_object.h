//
// Created by Darwin Yuan on 2020/9/22.
//

#ifndef NANO_CAF_FUTURE_CALLBACK_OBJECT_H
#define NANO_CAF_FUTURE_CALLBACK_OBJECT_H

#include <nano-caf/core/await/future_callback_base.h>

NANO_CAF_NS_BEGIN namespace detail {

template<typename R, typename F, typename A>
struct future_callback_object : future_callback_base<R, F, A> {
   using super = future_callback_base<R, F, A>;
   using super::super;

   auto on_future_ready() noexcept -> void override {
      if constexpr (std::is_void_v<R>) {
         get_result();
         super::set_value();
      } else {
         super::set_value(get_result());
      }
      super::do_commit();
   }

private:
   auto get_result() -> decltype(auto) {
      if constexpr (std::is_void_v<A>) {
         return super::f_();
      } else {
         return super::f_(super::subject_->get_value());
      }
   }
};

} NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_CALLBACK_OBJECT_H
