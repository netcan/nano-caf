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

NANO_CAF_NS_BEGIN

struct actor : actor_context {
   virtual ~actor() = default;

private:
   template<typename F>
   using async_future_t = std::shared_ptr<std::optional<typename callable_trait<std::decay_t<F>>::result_type>>;

   template<typename F>
   using async_future_type = result_t<async_future_t<F>>;

private:
   inline auto self_handle() const noexcept -> intrusive_actor_ptr override { return &self(); }
   inline auto get_system_actor_context() -> system_actor_context& override { return self().context(); }

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
      auto result = obj->get_future();
      self().context().schedule_job(*obj);
      return result;
   }

   template<typename METHOD, typename A, typename ... Args>
   inline auto request(typed_actor_handle<A>& to, Args&&...args)  {
      return to.template request<METHOD>(self_handle(), std::forward<Args>(args)...);
   }

   template<typename ... Args>
   inline auto with(Args&& ... args) {
      return [&](auto&& callback) {
         if((!async::is_optional_type<std::decay_t<decltype(args)>> || ...) ) {
            return status_t::invalid_data;
         }
         return detail::with_optionals(std::forward<decltype(callback)>(callback), async::get_optional(args)...)
            .with_value([this](auto future_cb) { return register_future_callback(future_cb); });
      };
   }

   template<typename Rep, typename Period>
   inline auto start_timer(std::chrono::duration<Rep, Period> const& d, bool periodic = false) -> result_t<timer_id_t> {
      return start_timer((uint64_t)std::chrono::microseconds(d).count(), periodic);
   }

   inline auto start_timer(timer_spec const& spec, bool periodic = false) -> result_t<timer_id_t> {
      return start_timer_(spec, periodic, nullptr);
   }

   inline auto stop_timer(timer_id_t timer_id) -> void {
      get_system_actor_context().stop_timer(self_handle(), timer_id);
   }

   template<typename F>
   inline auto after(timer_spec const& spec, F&& f) -> result_t<timer_id_t> {
      auto callback = std::make_shared<timeout_callback_t>(std::forward<F>(f));
      if(callback == nullptr) return status_t::out_of_mem;
      return start_timer_(spec, false, callback);
   }

   template<typename Rep, typename Period, typename F>
   inline auto after(std::chrono::duration<Rep, Period> const& d, F&& f) -> result_t<timer_id_t> {
      return after((uint64_t)std::chrono::microseconds(d).count(),
                   [f_ = std::forward<F>(f)](timer_id_t){ f_(); });
   }

   template<typename Rep, typename Period, typename F>
   inline auto repeat(std::chrono::duration<Rep, Period> const& d, F&& f) -> result_t<timer_id_t> {
      return repeat((uint64_t)std::chrono::microseconds(d).count(),
                    [f_ = std::forward<F>(f)](timer_id_t){ f_(); });
   }

   template<typename F>
   inline auto repeat(timer_spec const& spec, F&& f) -> result_t<timer_id_t> {
      auto callback = std::make_shared<timeout_callback_t>(std::forward<F>(f));
      if(callback == nullptr) return status_t::out_of_mem;
      return start_timer_(spec, true, callback);
   }

   virtual auto exit(exit_reason) noexcept -> void = 0;

private:
   auto start_timer_(timer_spec const& spec, bool periodic, std::shared_ptr<timeout_callback_t> callback) -> result_t<timer_id_t> {
      auto result = get_system_actor_context().start_timer(self_handle(), spec, periodic, std::move(callback));
      if(result.is_ok()) {
         on_timer_created();
      }
      return result;
   }

private:
   virtual auto self() const noexcept -> actor_control_block& = 0;
   virtual auto current_sender() const noexcept -> actor_handle = 0;
   virtual auto register_future_callback(future_callback*) noexcept -> status_t = 0;
   virtual auto on_timer_created() -> void = 0;

protected:
   virtual auto on_init() -> void {}
   virtual auto on_exit() -> void {}
   virtual auto handle_message(message&) noexcept -> task_result {
      return task_result::done;
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_H
