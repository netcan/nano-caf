//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_FUTURE_OBJECT_H
#define NANO_CAF_FUTURE_OBJECT_H

#include <nano-caf/core/await/detail/future_object_base.h>

NANO_CAF_NS_BEGIN namespace detail {

template<typename T, typename = void>
struct future_object;

template<typename T>
struct future_object<T, std::enable_if_t<std::is_move_constructible_v<T>>>
   : future_object_base {
   using super = future_object_base;
   using super::super;

   template<typename R, typename = std::enable_if_t<std::is_convertible_v<R, T>>>
   auto set_value(R &&value) noexcept -> void {
      if (super::present_) return;
      new(&storage_) T(std::forward<R>(value));
      super::present_ = true;
   }

   auto get_value() const noexcept -> T const & {
      return *reinterpret_cast<const T *>(&storage_);
   }

   ~future_object() override {
       if constexpr (std::is_trivially_destructible_v<T>) {
           if (super::present_) {
               get_value().~T();
           }
       }
   }

private:
   std::aligned_storage_t<sizeof(T), alignof(T)> storage_;
};

template<>
struct future_object<void> : future_object_base {
   using future_object_base::future_object_base;

   auto set_value() noexcept -> void {
      present_ = true;
   }
};

} NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_OBJECT_H
