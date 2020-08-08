//
// Created by Darwin Yuan on 2020/7/25.
//

#ifndef NANO_CAF_ACTOR_H
#define NANO_CAF_ACTOR_H

#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <nano-caf/core/actor/exit_reason.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/await/async_object.h>
#include <nano-caf/core/await/future_callback.h>
#include <optional>

NANO_CAF_NS_BEGIN

struct actor {
   virtual ~actor() = default;

private:
   template<typename F>
   using async_future_type = std::optional<std::shared_future<typename callable_trait<std::decay_t<F>>::return_type>>;

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

   template<typename ... Args>
   inline auto with(Args ... args) {
      return with_futures([this](future_callback* callback) -> bool {
            return register_future_callback(callback);
         }, args...);
   }

   virtual auto exit(exit_reason) noexcept -> void = 0;

private:
   auto self_handle() const noexcept -> intrusive_actor_ptr {
      return &self();
   }

private:
   virtual auto self() const noexcept -> actor_control_block& = 0;
   virtual auto current_sender() const noexcept -> actor_handle = 0;
   virtual auto register_future_callback(future_callback*) noexcept -> bool = 0;

protected:
   virtual auto on_init() -> void {}
   virtual auto on_exit() -> void {}
   virtual auto handle_message(message& msg) noexcept -> task_result {
      return task_result::done;
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_H
