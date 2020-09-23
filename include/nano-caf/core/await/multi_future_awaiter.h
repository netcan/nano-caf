//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_MULTI_FUTURE_AWAITER_H
#define NANO_CAF_MULTI_FUTURE_AWAITER_H

#include <nano-caf/core/await/promise_done_notifier.h>
#include <nano-caf/core/await/future.h>
#include <nano-caf/core/await/cancellable.h>
#include <nano-caf/core/await/cancellable_repository.h>
#include <nano-caf/core/await/future_awaiter.h>
#include <memory>

NANO_CAF_NS_BEGIN

template<typename F_CALLBACK, typename F_FAIL, typename ... Xs>
struct multi_future_awaiter
   : std::enable_shared_from_this<multi_future_awaiter<F_CALLBACK, F_FAIL, Xs...>>
   , cancellable
   , promise_done_notifier {
   static_assert(std::is_invocable_r_v<void, std::decay_t<F_FAIL>, status_t>,
                 "on_fail callback should take a status_t type");
   static_assert(std::is_invocable_r_v<void, std::decay_t<F_CALLBACK>, const Xs &...>,
                 "the callback should take correct parameters");
   static_assert(sizeof...(Xs) > 1, "should wait at least 2 futures");

   using super = std::enable_shared_from_this<multi_future_awaiter<F_CALLBACK, F_FAIL, Xs...>>;
   multi_future_awaiter(on_actor_context &context, F_CALLBACK &&f_callback, F_FAIL &&f_fail,
                        future<Xs> &... objects)
      : multi_future_awaiter(context, std::forward<F_CALLBACK>(f_callback), std::forward<F_FAIL>(f_fail),
                             objects.object_ ...) {
   }

   multi_future_awaiter(on_actor_context &context, F_CALLBACK &&f_callback, F_FAIL &&f_fail,
                        std::tuple<std::shared_ptr<detail::future_object<Xs>>...>&& objects)
      :  context_{context}
      ,  objects_{std::move(objects)}
      ,  callback_{std::forward<F_CALLBACK>(f_callback)}
      ,  on_fail_{std::forward<F_FAIL>(f_fail)}, num_of_pending_(sizeof...(Xs)) {
      init(std::index_sequence_for<Xs...>{});
   }

private:
   multi_future_awaiter(on_actor_context &context, F_CALLBACK &&f_callback, F_FAIL &&f_fail,
                        std::shared_ptr<detail::future_object<Xs>>... objects)
      : context_{context}, objects_{std::move(objects)...}, callback_{std::forward<F_CALLBACK>(f_callback)},
        on_fail_{std::forward<F_FAIL>(f_fail)}, num_of_pending_(sizeof...(Xs)) {
      init(std::index_sequence_for<Xs...>{});
   }

public:
   inline auto destroyed() const noexcept -> bool { return destroyed_; }

private:
   auto destroy() {
      context_.remove_cancellable(this);
      destroyed_ = true;
   }

   template<std::size_t ... I>
   auto on_done(std::index_sequence<I...>) {
      std::invoke(callback_, std::get<I>(objects_)->get_value() ...);
   }

   auto on_promise_done() noexcept -> void override {
      if (--num_of_pending_ == 0) {
         on_done(std::index_sequence_for<Xs...>{});
         destroy();
      }
   }

   auto cancel(status_t cause) noexcept -> void override {
      if (!destroyed_) {
         on_fail_(cause);
         destroy();
      }
   }

   template<std::size_t I>
   auto init() {
      auto &&object = std::get<I>(objects_);
      if (object->ready()) {
         num_of_pending_--;
      }
   }

   template<std::size_t ... I>
   auto init(std::index_sequence<I...>) {
      (init<I>(), ...);
      if (num_of_pending_ == 0) {
         std::invoke(callback_, std::get<I>(objects_)->get_value() ...);
         destroyed_ = true;
      }
   }

   template<std::size_t I>
   auto register_single_notifier() {
      auto &&object = std::get<I>(objects_);
      if (!object->ready()) {
         object->add_notifier(super::shared_from_this());
      }
   }

   template<std::size_t ... I>
   auto register_notifier(std::index_sequence<I...>) {
      (register_single_notifier<I>(), ...);
   }

public:
   auto register_notifier() {
      register_notifier(std::index_sequence_for<Xs...>{});
   }

private:
   on_actor_context &context_;
   std::tuple<std::shared_ptr<detail::future_object<Xs>>...> objects_;
   F_CALLBACK callback_;
   F_FAIL on_fail_;
   std::size_t num_of_pending_;
   bool destroyed_{false};
};

NANO_CAF_NS_END

#endif //NANO_CAF_MULTI_FUTURE_AWAITER_H
