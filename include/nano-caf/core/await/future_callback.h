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

template<typename T>
struct optional_future_trait;

template<typename T>
struct optional_future_trait<std::optional<std::shared_future<T>>> {
   using type = T;
};

template<typename ... Args>
struct future_set {
   future_set(Args& ... args) : futures_{std::move(args)...} {}

   template<size_t ... I>
   auto valid(std::index_sequence<I...>) const -> bool {
      return ((std::get<I>(futures_) != std::nullopt) && ...);
   }

   template<typename Tp>
   static constexpr auto is_future_done(const std::shared_future<Tp>& future) noexcept -> bool {
      return future.wait_for(std::chrono::nanoseconds{0}) == std::future_status::ready;
   }

   template<size_t ... I>
   auto done(std::index_sequence<I...>) const -> bool {
      return (is_future_done(*std::get<I>(futures_)) && ...);
   }

   template<size_t ... I, typename F>
   auto invoke(F&& f, std::index_sequence<I...> is) const -> bool {
      if(!done(is)) return false;
      f((*std::get<I>(futures_)).get()...);
      return true;
   }

private:
   mutable std::tuple<Args...> futures_;
};

template<typename T, typename ... Args>
struct with_futures {
   with_futures(T registry, Args&...args)
      : registry_{std::move(registry)}
      , futures_{args...}
   {}

   template<typename F>
   auto operator()(F&& f) -> bool {
      using trait = callable_trait<std::decay_t<F>>;
      static_assert(std::is_same_v<typename trait::return_type, void>);
      using args_type = typename trait::args_type;
      using deduced_args_type = type_list<typename optional_future_trait<std::decay_t<Args>>::type...>;
      static_assert(std::is_same_v<args_type, deduced_args_type>);
      using seq_type = std::make_index_sequence<sizeof...(Args)>;

      if(!futures_.valid(seq_type{})) return false;
      if(futures_.invoke(std::forward<F>(f), seq_type{})) return true;

      return registry_(new generic_future_callback(
         [=, futures = std::move(futures_)]() mutable -> bool {
            return futures.invoke(std::move(f), seq_type{});
         }));
   }

private:
   T registry_;
   future_set<Args...> futures_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_CALLBACK_H
