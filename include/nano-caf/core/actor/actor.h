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

struct actor {
   virtual ~actor() = default;

private:
   template<typename F>
   using async_future_type = std::optional<std::shared_future<typename callable_trait<std::decay_t<F>>::result_type>>;

private:
   template<typename F, typename ... Args>
   auto wait_futures(F&& f, Args&& ...args) -> status_t {
      static_assert(std::is_invocable_r_v<void, F, decltype(std::declval<Args>().get())...>);
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
      return register_future_callback(callback);
   }

protected:
   template<typename T, message::category CATEGORY = message::normal, typename ... Args>
   inline auto send(actor_handle& to, Args&& ... args) noexcept {
      return to.send<T, CATEGORY>(self_handle(), std::forward<Args>(args)...);
   }

   template<typename T, message::category CATEGORY = message::normal, typename ... Args>
   inline auto reply(Args&& ... args) noexcept {
      auto sender = current_sender();
      if(!sender.exists()) return enq_result::null_sender;
      return sender.send<T, CATEGORY>(self_handle(), std::forward<Args>(args)...);
   }

   template<typename T, typename ... Ts>
   inline auto spawn(Ts&& ... args) noexcept -> actor_handle {
      return self().context().spawn<T>(std::forward<Ts>(args)...);
   }


   template<typename F, typename ... Args>
   inline auto async(F&& f, Args&&...args) -> async_future_type<F> {
      auto obj = make_async_object(self_handle(), std::forward<F>(f), std::forward<Args>(args)...);
      if(obj == nullptr) {
         return std::nullopt;
      }
      auto result = std::optional{std::shared_future{obj->get_future()}};
      self().context().schedule_job(*obj);
      return result;
   }

   template<typename A, typename METHOD, typename ... Args>
   inline auto request(typed_actor_handle<A>& to, METHOD method, Args&&...args)  {
      to.request(self_handle(), method, std::forward<Args>(args)...);
   }

   template<typename ... Args>
   inline auto with(Args&& ... args) {
      return [&](auto&& callback) {
         if(((!args.has_value()) || ...) ) {
            return status_t::failed;
         }
         return wait_futures(std::forward<decltype(callback)>(callback), *args...);
      };
   }

   virtual auto exit(exit_reason) noexcept -> void = 0;

private:
   auto self_handle() const noexcept -> intrusive_actor_ptr {
      return &self();
   }

private:
   virtual auto self() const noexcept -> actor_control_block& = 0;
   virtual auto current_sender() const noexcept -> actor_handle = 0;
   virtual auto register_future_callback(future_callback*) noexcept -> status_t = 0;

protected:
   virtual auto on_init() -> void {}
   virtual auto on_exit() -> void {}
   virtual auto handle_message(message& msg) noexcept -> task_result {
      return task_result::done;
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_H
