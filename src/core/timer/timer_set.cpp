//
// Created by Darwin Yuan on 2020/8/22.
//

#include <nano-caf/core/timer/timer_set.h>
#include <nano-caf/util/likely.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <nano-caf/core/actor/shutdown_notifier.h>

NANO_CAF_NS_BEGIN

namespace {
   inline auto send_timeout_msg_to_actor(const start_timer_msg* msg) {
      actor_handle(msg->actor).send<timeout_msg>(msg->id, msg->callback);
   }

   inline auto get_due(const start_timer_msg* msg) {
      return msg->spec.left_match([&](auto const& duration) {
         return msg->issue_time_point + std::chrono::microseconds(duration);
      });
   }
}

#define timer_due(timer) timer->first

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::add_timer(std::unique_ptr<message> msg) -> status_t {
   if(__unlikely(msg == nullptr)) return status_t::null_msg;

   auto start_msg = msg->body<start_timer_msg>();
   if(__unlikely(start_msg == nullptr)) return status_t::failed;

   auto due = get_due(start_msg);
   if(__unlikely(due < std::chrono::steady_clock::now())) {
      send_timeout_msg_to_actor(start_msg);
      if(!start_msg->is_periodic) {
         return status_t::ok;
      }
   }

   auto iterator = timers_.emplace(due, std::move(msg));
   auto actor_id = start_msg->actor.actor_id();
   actor_indexer_.emplace(actor_id, iterator);

   return status_t::ok;
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::remove_timer(intptr_t actor_id, timer_id_t msg_id) -> void {
   auto range = actor_indexer_.equal_range(actor_id);
   for(auto i = range.first; i != range.second; ++i) {
      if(i->second->second->body<start_timer_msg>()->id == msg_id) {
         timers_.erase(i->second);
         actor_indexer_.erase(i);
         break;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::remove_index(intptr_t actor_id, const timers::iterator& iterator) -> void {
   auto range = actor_indexer_.equal_range(actor_id);
   for(auto i = range.first; i != range.second; ++i) {
      if(i->second == iterator) {
         actor_indexer_.erase(i);
         break;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::update_index(intptr_t actor_id, timers::iterator const& from, timers::iterator const& to) -> void {
   auto range = actor_indexer_.equal_range(actor_id);
   for(auto i = range.first; i != range.second; ++i) {
      if(i->second == from) {
         i->second = to;
         break;
      }
   }
}
/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::clear_actor_timers(intptr_t actor_id) -> void {
   auto range = actor_indexer_.equal_range(actor_id);
   for(auto i = range.first; i != range.second; ++i) {
      timers_.erase(i->second);
   }
   actor_indexer_.erase(range.first, range.second);
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::handle_msg(std::unique_ptr<message> msg) -> void {
   switch(msg->msg_type_id_) {
      case start_timer_msg::type_id:
         add_timer(std::move(msg));
         break;
      case stop_timer_msg::type_id: {
         auto stop_msg = msg->body<stop_timer_msg>();
         remove_timer(stop_msg->actor, stop_msg->id);
         break;
      }
      case clear_actor_timer_msg::type_id: {
         auto clear_msg = msg->body<clear_actor_timer_msg>();
         clear_actor_timers(clear_msg->actor);
         break;
      }
      default: break;
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////
namespace {
   inline auto cleanup_msgs(message* msgs) {
      while(msgs != nullptr) {
         std::unique_ptr<message> head{msgs};
         msgs = head->next_;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::handle_msgs(message* msgs, const shutdown_notifier& shutdown) -> status_t {
   while(msgs != nullptr) {
      auto status = check_timer_due(shutdown);
      if(__unlikely(status == status_t::system_shutdown)) {
         cleanup_msgs(msgs);
         return status_t::system_shutdown;
      }

      std::unique_ptr<message> head{msgs};
      msgs = head->next_;
      head->next_ = nullptr;

      handle_msg(std::move(head));
   }
   return status_t::ok;
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::check_timer_due(const shutdown_notifier& shutdown) -> status_t {
   while(!timers_.empty()) {
      if(__unlikely(shutdown.shutdown_notified())) {
         return status_t::system_shutdown;
      }

      auto timer = timers_.begin();
      if(timer_due(timer) > std::chrono::steady_clock::now()) {
         break;
      }

      auto msg = timer->second->body<start_timer_msg>();

      send_timeout_msg_to_actor(msg);

      if(msg->is_periodic) {
         msg->issue_time_point = timer_due(timer);
         auto sched_msg = std::move(timer->second);

         timers_.erase(timer);
         auto iterator = timers_.emplace(get_due(msg), std::move(sched_msg));
         update_index(msg->actor.actor_id(), timer, iterator);
      } else {
         timers_.erase(timer);
         remove_index(msg->actor.actor_id(), timer);
      }
   }

   return status_t::ok;
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::wait_for_timer_due(cv_notifier& cv, shutdown_notifier& shutdown) -> status_t {
   if(cv.wait_until(get_recent_due()) == std::cv_status::timeout) {
      return check_timer_due(shutdown);
   }
   return shutdown.shutdown_notified() ? status_t::system_shutdown : status_t::ok;
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::reset() -> void {
   actor_indexer_.clear();
   timers_.clear();
}

NANO_CAF_NS_END