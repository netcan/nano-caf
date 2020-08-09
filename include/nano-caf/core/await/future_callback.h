//
// Created by Darwin Yuan on 2020/7/27.
//

#ifndef NANO_CAF_FUTURE_CALLBACK_H
#define NANO_CAF_FUTURE_CALLBACK_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/util/callable_trait.h>
#include <type_traits>
#include <functional>
#include <optional>

NANO_CAF_NS_BEGIN

struct future_callback {
   virtual auto invoke() noexcept -> bool = 0;
   virtual ~future_callback() = default;
};

template<typename F>
struct generic_future_callback : future_callback {
   generic_future_callback(F&& f) : f(std::move(f)) {}

   auto invoke() noexcept -> bool override {
      return f();
   }

private:
   F f;
};

template<typename ... Args>
struct future_set {
   future_set(Args& ... args) : futures_{std::move(args)...} {}

   template<typename Tp>
   static constexpr auto is_future_done(const Tp& future) noexcept -> bool {
      return future.wait_for(std::chrono::nanoseconds{0}) == std::future_status::ready;
   }

   template<size_t ... I>
   auto done(std::index_sequence<I...>) const -> bool {
      return (is_future_done(std::get<I>(futures_)) && ...);
   }

   template<size_t ... I, typename F>
   auto invoke(F&& f, std::index_sequence<I...> is) const -> bool {
      if(!done(is)) return false;
      f(std::get<I>(futures_).get()...);
      return true;
   }

   template<typename F>
   auto invoke(F&& f) const -> bool {
      return invoke(std::forward<F>(f), std::make_index_sequence<sizeof...(Args)>{});
   }

private:
   mutable std::tuple<Args...> futures_;
};

namespace detail {
   template<typename F, typename ... Args>
   auto with_futures(F&& f, Args&& ...args) -> either<future_callback*, status_t> {
      static_assert(std::is_invocable_r_v<void, F, decltype(std::declval<std::decay_t<Args>>().get())...>);
      using seq_type = std::make_index_sequence<sizeof...(Args)>;
      future_set<std::decay_t<Args>...> futures{args...};
      if(futures.invoke(std::forward<F>(f), seq_type{})) return status_t::ok;

      auto callback = new generic_future_callback(
         [=, futures = std::move(futures)]() mutable -> bool {
            return futures.invoke(std::move(f));
         });
      if(callback == nullptr) {
         return status_t::out_of_mem;
      }
      return callback;
   }
}

namespace detail {
   template<typename T, typename FUTURE>
   struct request_then {
      request_then(T& registry, FUTURE& future)
         : registry_{std::move(registry)}
         , future_{std::move(future)} {}

      template<typename F_SUCC, typename F_FAIL>
      auto then(F_SUCC&& f_succ, F_FAIL&& f_fail) -> status_t {
         if(future_.left_present()) {
            auto l = [succ = std::move(f_succ), fail = std::move(f_fail)](auto result) {
               result.match(succ, fail);
            };
            return with_futures(std::move(l), future_.left()).match(
               [&](auto future_cb) { return registry_(future_cb); },
               [&](auto failure) { f_fail(failure); return failure; }
            );
         } else {
            f_fail(future_.right());
            return future_.right();
         }
      }

   private:
      T registry_;
      FUTURE future_;
   };
}


NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_CALLBACK_H
