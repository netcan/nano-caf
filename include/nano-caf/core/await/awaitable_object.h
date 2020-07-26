//
// Created by Darwin Yuan on 2020/7/27.
//

#ifndef NANO_CAF_AWAITABLE_OBJECT_H
#define NANO_CAF_AWAITABLE_OBJECT_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/resumable.h>
#include <type_traits>
#include <functional>
#include <future>

NANO_CAF_NS_BEGIN

template <typename F, typename R>
struct async_object : resumable {
   async_object(F&& f) : f{std::move(f)} {}

   virtual auto resume() noexcept -> result override{
      auto result = f();
      promise.set_value(result);
      return result::done;
   }

   auto get_future() {
      return promise.get_future();
   }

private:
   std::promise<R> promise;
   F f;
};

template<typename T, typename ... Args, typename = std::enable_if_t<std::is_invocable_v<T, Args...>>>
auto make_async_object(T&& callable, Args&& ... args) {
   auto bind_obj = std::bind(std::forward<T>(callable), std::forward<Args>(args)...);
   return new async_object<decltype(bind_obj), decltype(bind_obj())>{std::move(bind_obj)};
}


NANO_CAF_NS_END

#endif //NANO_CAF_AWAITABLE_OBJECT_H
