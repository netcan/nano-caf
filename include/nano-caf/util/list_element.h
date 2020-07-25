//
// Created by Darwin Yuan on 2020/7/25.
//

#ifndef NANO_CAF_LIST_ELEMENT_H
#define NANO_CAF_LIST_ELEMENT_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

struct list_element {
   list_element* next;

   virtual ~list_element() = default;

   template<typename T>
   auto to_value() -> T* {
      return reinterpret_cast<T*>(to_value_ptr());
   }

private:
   virtual auto to_value_ptr() -> void* = 0;
};

NANO_CAF_NS_END

#endif //NANO_CAF_LIST_ELEMENT_H
