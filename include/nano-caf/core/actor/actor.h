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
#include <nano-caf/core/await/multi_future.h>
#include <nano-caf/core/actor/on_actor_context.h>

NANO_CAF_NS_BEGIN

struct actor : actor_context, private on_actor_context {
   virtual ~actor() = default;

private:
   template<typename F>
   using async_future_t = future<typename callable_trait<std::decay_t<F>>::result_type>;

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
   inline auto async(F&& f, Args&&...args) -> async_future_t<F> {
      using R = std::invoke_result_t<F, Args...>;
      return future<R>{*this, [=, &context = self().context(), self = self_handle(), f = std::forward<F>(f), args = std::make_tuple(std::forward<std::decay_t<Args>>(args) ...)]
         (detail::future_object_sp<R> obj) mutable {
         auto async_obj = make_async_object(std::move(obj), self, std::move(f), std::move(args));
         if(async_obj == nullptr) {
            return status_t::out_of_mem;
         }
         context.schedule_job(*async_obj);
         return status_t::ok;
      }};
   }

   template<typename METHOD, typename A, typename ... Args>
   inline auto request(typed_actor_handle<A>& to, Args&&...args)  {
      return to.template request<METHOD>(self_handle(), *this, std::forward<Args>(args)...);
   }

   template<typename ... Xs>
   inline auto with(future<Xs>& ... args) {
      return multi_future<Xs...>(*this, args ...);
   }

   template<typename Rep, typename Period>
   inline auto start_timer(std::chrono::duration<Rep, Period> const& d, bool periodic = false) -> result_t<timer_id_t> {
      return start_timer((uint64_t)std::chrono::microseconds(d).count(), periodic);
   }

   inline auto start_timer(timer_spec const& spec, bool periodic = false) -> result_t<timer_id_t> {
      return start_timer(spec, periodic, nullptr);
   }

   inline auto stop_timer(timer_id_t timer_id) -> void override{
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
      return start_timer(spec, true, callback);
   }

   virtual auto exit(exit_reason) noexcept -> void = 0;

private:
   auto start_timer(timer_spec const& spec, bool periodic, std::shared_ptr<timeout_callback_t> callback) -> result_t<timer_id_t> override {
      auto result = get_system_actor_context().start_timer(self_handle(), spec, periodic, std::move(callback));
      if(result.is_ok()) {
         on_timer_created();
      }
      return result;
   }

private:
   virtual auto self() const noexcept -> actor_control_block& = 0;
   virtual auto current_sender() const noexcept -> actor_handle = 0;
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
