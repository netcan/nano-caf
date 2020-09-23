////
//// Created by Darwin Yuan on 2020/7/27.
////
//
//#ifndef NANO_CAF_FUTURE_CALLBACK_H
//#define NANO_CAF_FUTURE_CALLBACK_H
//
//#include <nano-caf/nano-caf-ns.h>
//#include <nano-caf/core/msg/message.h>
//#include <nano-caf/util/callable_trait.h>
//#include <nano-caf/util/result_t.h>
//#include <type_traits>
//#include <functional>
//#include <optional>
//
//NANO_CAF_NS_BEGIN
//
//struct future_callback {
//   virtual auto invoke() noexcept -> bool = 0;
//   virtual ~future_callback() = default;
//};
//
//template<typename F>
//struct generic_future_callback : future_callback {
//   generic_future_callback(F&& f) : f(std::move(f)) {}
//
//   auto invoke() noexcept -> bool override {
//      return f();
//   }
//
//private:
//   F f;
//};
//
//template<typename ... Args>
//struct optional_set {
//   template<typename ... Xs>
//   optional_set(Xs&& ... xs) : futures_{std::forward<Xs>(xs)...} {}
//
//   template<size_t ... I>
//   auto done(std::index_sequence<I...>) const -> bool {
//      return (std::get<I>(futures_)->has_value() && ...);
//   }
//
//   template<size_t ... I, typename F>
//   auto invoke(F&& f, std::index_sequence<I...> is) const -> bool {
//      if(!done(is)) return false;
//      f(std::get<I>(futures_)->value()...);
//      return true;
//   }
//
//   template<typename F>
//   auto invoke(F&& f) const -> bool {
//      return invoke(std::forward<F>(f), std::make_index_sequence<sizeof...(Args)>{});
//   }
//
//private:
//   mutable std::tuple<Args...> futures_;
//};
//
//namespace detail {
//   template<typename F, typename ... Args>
//   auto with_optionals(F &&f, Args &&...args) -> result_t<future_callback *> {
//      static_assert(std::is_invocable_r_v<void, F, decltype(std::declval<std::decay_t<Args>>()->value())...>);
//      using seq_type = std::make_index_sequence<sizeof...(Args)>;
//      optional_set<std::decay_t<Args>...> futures{std::forward<Args>(args)...};
//      if (futures.invoke(std::forward<F>(f), seq_type{})) return status_t::ok;
//
//      auto callback = new generic_future_callback(
//         [futures = std::move(futures), func = std::move(f)]() mutable -> bool {
//            return futures.invoke(func);
//         });
//      if (callback == nullptr) {
//         return status_t::out_of_mem;
//      }
//      return callback;
//   }
//}
//
//namespace async {
//   template<typename T>
//   constexpr bool is_future_type = false;
//
//   template<typename T>
//   constexpr bool is_future_type<std::shared_future<T>> = true;
//
//   template<typename T>
//   constexpr bool is_future_type<std::future<T>> = true;
//
//
//   template<typename T>
//   constexpr bool is_optional_type = false;
//
//   template<typename T>
//   constexpr bool is_optional_type<result_t<std::shared_ptr<std::optional<T>>>> = true;
//
//   template<typename T>
//   auto is_optional_valid(const T& f) -> std::enable_if_t<is_optional_type<T>, bool> {
//      return f.match(
//         [](auto& f) { return f != nullptr; },
//         [](auto) { return false; });
//   }
//
//   template<typename T>
//   auto get_optional(const result_t<std::shared_ptr<std::optional<T>>>& args) -> const std::shared_ptr<std::optional<T>>& {
//      return *args;
//   }
//
//   template<typename T>
//   auto is_future_valid(const T& f) -> std::enable_if_t<is_future_type<T>, bool> {
//      return f.valid();
//   }
//
//   template<typename T>
//   auto is_future_valid(const result_t<T>& f) -> std::enable_if_t<is_future_type<T>, bool> {
//      return f.match(
//         [](auto& f) { return f.valid(); },
//         [](auto) { return false; });
//   }
//
//   template<typename T>
//   auto get_future(T& f) -> std::enable_if_t<is_future_type<T>, T&>{
//      return f;
//   }
//
//   template<typename T>
//   auto get_future(result_t<T>& f) -> std::enable_if_t<is_future_type<T>, T&> {
//      return *f;
//   }
//}
//
//NANO_CAF_NS_END
//
//#endif //NANO_CAF_FUTURE_CALLBACK_H
