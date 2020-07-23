//
// Created by Darwin Yuan on 2020/7/23.
//

#ifndef NANO_CAF_INTRUSIVE_PTR_H
#define NANO_CAF_INTRUSIVE_PTR_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

template<typename T>
struct intrusive_ptr {
   intrusive_ptr() noexcept = default;
   intrusive_ptr(T* ptr) noexcept : ptr_(ptr) {}

private:
   T* ptr_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_INTRUSIVE_PTR_H
