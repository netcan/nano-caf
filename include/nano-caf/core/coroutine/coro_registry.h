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
   auto exists(std::coroutine_handle<> coro) const noexcept -> bool {
      return coro.address() != nullptr &&
             coroutines_.find(coro.address()) != coroutines_.end();
   }

   auto on_create(std::coroutine_handle<> coro) noexcept {
      if(coro.address() == nullptr) {
         return;
      }
      coroutines_.insert(coro.address());
   }

   auto on_destroy(std::coroutine_handle<> coro) noexcept {
      if(coro.address() == nullptr) {
         return;
      }
      coroutines_.erase(coro.address());
   }

   ~coro_registry() noexcept {
      for(auto v: coroutines_) {
         std::coroutine_handle<>::from_address(v).destroy();
      }
   }

private:
   std::unordered_set<void*> coroutines_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_CORO_REGISTRY_H
