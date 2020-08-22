//
// Created by Darwin Yuan on 2020/8/22.
//

#include <nano-caf/core/timer/timer_scheduler.h>
#include <nano-caf/core/msg/make_message.h>
#include <nano-caf/util/likely.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <iostream>

NANO_CAF_NS_BEGIN

auto timer_scheduler::go_sleep() -> void {
   if(timers_.empty()) {
      notifier_.wait([this]() {
         return shutdown.load(std::memory_order_relaxed) || !msg_queue_.blocked();
      });
   } else {
      if(notifier_.wait_until(timers_.begin()->first) == std::cv_status::timeout) {
         timer_set::on_timeout(shutdown);
      }
   }
}

auto timer_scheduler::handle_msgs(message* msgs) -> void {
   while(msgs != nullptr) {
      std::unique_ptr<message>head{msgs};
      msgs = head->next_;
      head->next_ = nullptr;
      switch(head->msg_type_id_) {
      case start_timer_msg::type_id:
         timer_set::add_timer(std::move(head));
         break;
      case stop_timer_msg::type_id: {
         auto stop_msg = head->body<stop_timer_msg>();
         timer_set::remove_timer(stop_msg->actor, stop_msg->id);
         break;
      }
      case clear_actor_timer_msg::type_id: {
         auto clear_msg = head->body<clear_actor_timer_msg>();
         timer_set::clear_actor_timers(clear_msg->actor);
         break;
      }
      default: break;
      }

      if(__unlikely(!shutdown.load())) {
         while(msgs != nullptr) {
            msgs = head->next_;
            delete msgs;
         }
         break;
      }
   }
}

auto timer_scheduler::schedule() -> void {
   while(1) {
      if(shutdown.load(std::memory_order_relaxed)) break;
      auto msgs = msg_queue_.take_all();
      if(msgs == nullptr) {
         if(msg_queue_.try_block()) {
            go_sleep();
         }
      } else {
         handle_msgs(msgs);
         timer_set::on_timeout(shutdown);
      }
   }
}

auto timer_scheduler::start() -> void {
   thread_ = std::thread([this]{ schedule(); });
}

auto timer_scheduler::stop() -> void {
   shutdown.store(true, std::memory_order_relaxed);
   notifier_.wake_up();
   thread_.join();
}

auto timer_scheduler::start_timer(intrusive_actor_ptr sender, const duration& duration, bool periodic) -> result_t<uint64_t> {
   if(__unlikely(!sender)) {
      return status_t::null_sender;
   }

   timer_id id = timer_id_.fetch_add(1, std::memory_order_relaxed);
   switch(msg_queue_.enqueue(make_message<start_timer_msg>(
      id, std::move(sender), duration, std::chrono::system_clock::now(), periodic))) {
      case enq_result::ok: return id;
      case enq_result::blocked: notifier_.wake_up(); return status_t::ok;
      case enq_result::null_msg: return status_t::null_msg;
      case enq_result::closed:   return status_t::msg_queue_closed;
      default: return status_t::failed;
   }
}

auto timer_scheduler::stop_timer(const intrusive_actor_ptr& self, timer_id id) -> void {
   switch(msg_queue_.enqueue(make_message<stop_timer_msg>(self.actor_id(), id))) {
      case enq_result::blocked: notifier_.wake_up(); break;
      default: break;
   }
}

auto timer_scheduler::clear_actor_timer(const intrusive_actor_ptr& sender) -> void {
   if(__unlikely(!sender)) return;
   switch(msg_queue_.enqueue(make_message<clear_actor_timer_msg>(sender.actor_id()))) {
      case enq_result::blocked: notifier_.wake_up(); break;
      default: break;
   }
}

NANO_CAF_NS_END
