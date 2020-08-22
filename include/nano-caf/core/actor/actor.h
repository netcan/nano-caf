//
// Created by Darwin Yuan on 2020/7/25.
//

#ifndef NANO_CAF_ACTOR_H
#define NANO_CAF_ACTOR_H

#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <nano-caf/core/actor/exit_reason.h>
#include <nano-caf/core/actor/typed_actor_handle.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/await/async_object.h>
#include <nano-caf/core/await/future_callback.h>
#include <optional>
#include <iostream>

NANO_CAF_NS_BEGIN

struct actor : actor_context {
   virtual ~actor() = default;

private:
   template<typename F>
   using async_future_t = std::shared_future<typename callable_trait<std::decay_t<F>>::result_type>;

   template<typename F>
   using async_future_type = either<async_future_t<F>, status_t>;

protected:
   template<typename T, message::category CATEGORY = message::normal, typename ... Args>
   inline auto reply(Args&& ... args) noexcept {
      auto sender = current_sender();
      if(!sender.exists()) return status_t::null_sender;
      return sender.send<T, CATEGORY>(self_handle(), std::forward<Args>(args)...);
   }

   template<typename F, typename ... Args>
   inline auto async(F&& f, Args&&...args) -> async_future_type<F> {
      auto obj = make_async_object(self_handle(), std::forward<F>(f), std::forward<Args>(args)...);
      if(obj == nullptr) {
         return status_t::out_of_mem;
      }
      auto result = obj->get_future().share();
      self().context().schedule_job(*obj);
      return result;
   }

   template<typename METHOD, typename A, typename ... Args>
   inline auto request(typed_actor_handle<A>& to, Args&&...args)  {
      auto result = to.template request<METHOD>(self_handle(), std::forward<Args>(args)...);
      auto l = [this](auto future_cb) { return register_future_callback(future_cb); };
      return detail::request_then<decltype(l), decltype(result)>{l, result};
   }

   template<typename ... Args>
   inline auto with(Args&& ... args) {
      return [&](auto&& callback) {
         if(((!async::is_future_valid(args)) || ...) ) {
            return status_t::invalid_data;
         }
         return detail::with_futures(std::forward<decltype(callback)>(callback), async::get_future(args)...)
            .with_value([this](auto future_cb) { return register_future_callback(future_cb); });
      };
   }

   auto start_timer(const duration& duration, bool periodic = false) -> result_t<uint64_t> {
      return get_system_actor_context().start_timer(self_handle(), duration, periodic);
   }

   auto stop_timer(uint64_t timer_id)  {
      return get_system_actor_context().stop_timer(self_handle(), timer_id);
   }

   virtual auto exit(exit_reason) noexcept -> void = 0;

private:
   auto self_handle() const noexcept -> intrusive_actor_ptr override {
      return &self();
   }

   virtual auto get_system_actor_context() -> system_actor_context& override {
      return self().context();
   }

private:
   virtual auto self() const noexcept -> actor_control_block& = 0;
   virtual auto current_sender() const noexcept -> actor_handle = 0;
   virtual auto register_future_callback(future_callback*) noexcept -> status_t = 0;

protected:
   virtual auto on_init() -> void {}
   virtual auto on_exit() -> void {}
   virtual auto handle_message(message&) noexcept -> task_result {
      return task_result::done;
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_H
