//
// Created by Darwin Yuan on 2020/9/16.
//

#ifndef NANO_CAF_CORO_REGISTRY_H
#define NANO_CAF_CORO_REGISTRY_H

#include <nano-caf/nano-caf-ns.h>
#include <coroutine>
#include <unordered_set>

NANO_CAF_NS_BEGIN

struct coro_registry {
   auto exists(void* handle) -> bool {
      return coroutines_.find(handle) != coroutines_.end();
   }

   auto on_create(void* handle) {
      if(handle == nullptr) {
         return;
      }
      coroutines_.insert(handle);
   }

   auto on_destroy(void* handle) {
      if(handle == nullptr) {
         return;
      }
      coroutines_.erase(handle);
   }

   ~coro_registry() {
      for(auto v: coroutines_) {
         std::coroutine_handle<>::from_address(v).destroy();
      }
   }

private:
   std::unordered_set<void*> coroutines_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_CORO_REGISTRY_H
