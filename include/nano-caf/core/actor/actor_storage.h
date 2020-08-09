//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_ACTOR_STORAGE_H
#define NANO_CAF_ACTOR_STORAGE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message.h>
#include <nano-caf/core/actor/lifo_inbox.h>
#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/await/future_callback.h>
#include <vector>

NANO_CAF_NS_BEGIN

template<typename T>
struct actor_storage  {
   template<typename ... Ts>
   actor_storage(actor_context& context, Ts&& ... args)
      : control{context, data_dtor, block_dtor} {
      auto p = new (&value_) internal_actor(std::forward<Ts>(args)...);
      p->init_handler();
   }

    ~actor_storage() {
        //static_assert(offsetof(actor_storage, control) == 0);
    }

private:
   static auto data_dtor(sched_actor* ptr) -> void {
      auto p = static_cast<internal_actor*>(ptr);
      p->exit_handler();
      p->~internal_actor();
   }

   static auto block_dtor(actor_control_block* ptr) noexcept -> void {
      delete reinterpret_cast<actor_storage<T>*>(ptr);
   }

public:
   static_assert(sizeof(actor_control_block) <= CACHE_LINE_SIZE);
   actor_control_block control;

private:
   char padding[CACHE_LINE_SIZE - sizeof(control)];

   struct internal_actor : sched_actor, private T {
      template<typename ... Args>
      internal_actor(Args&&...args)
         : sched_actor(true)
         , T{std::forward<Args>(args)...} {}

      auto exit(exit_reason reason) noexcept -> void override {
         sched_actor::exit_(reason);
      }

      auto self() const noexcept -> actor_control_block& override {
         return *sched_actor::to_ctl();
      }

      auto init_handler() noexcept -> void { T::on_init(); }
      auto exit_handler() noexcept -> void { T::on_exit(); }

      auto check_futures() {
         for (auto it = futures_.begin(); it != futures_.end(); ) {
            if ((*it)->invoke()) {
               delete *it;
               it = futures_.erase(it);
            } else {
               ++it;
            }
         }
      }

      auto user_defined_handle_msg(message& msg) noexcept -> task_result override {
         if(msg.is_future_response()) {
            check_futures();
            return task_result::resume;
         } else {
            return T::handle_message(msg);
         }
      }

      auto current_sender() const noexcept -> actor_handle override {
         return get_current_sender();
      }

      auto register_future_callback(future_callback* future) noexcept -> status_t override {
         if(future == nullptr) return status_t::null_ptr;
         futures_.push_back(future);
         return status_t::ok;
      }

      ~internal_actor() {
         for (auto& i : futures_) {
            delete i;
         }
      }

      std::vector<future_callback*> futures_{};
   };

   union { internal_actor value_; };
};


NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_STORAGE_H
