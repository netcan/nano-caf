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
   static constexpr auto is_future_done(const std::shared_future<Tp>& future) noexcept -> bool {
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

template<typename T, typename ... Args>
struct with_futures {
   template<typename F>
   auto operator()(F&& f) -> bool {
      static_assert(std::is_invocable_r_v<void, F, Args...>);
      using seq_type = std::make_index_sequence<sizeof...(Args)>;

      if(futures_.invoke(std::forward<F>(f), seq_type{})) return true;

      return registry_(new generic_future_callback(
         [=, futures = std::move(futures_)]() mutable -> bool {
            return futures.invoke(std::move(f));
         }));
   }

private:
   T registry_;
   future_set<Args...> futures_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_CALLBACK_H
