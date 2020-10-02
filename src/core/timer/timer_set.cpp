//
// Created by Darwin Yuan on 2020/8/22.
//

#include <nano-caf/core/timer/timer_set.h>
#include <nano-caf/util/likely.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <nano-caf/core/actor/shutdown_notifier.h>

NANO_CAF_NS_BEGIN

namespace {
   inline auto send_timeout_msg_to_actor(start_timer_msg* msg) -> status_t {
      if(__unlikely(msg->is_periodic)) {
         return actor_handle(msg->actor.lock()).send<timeout_msg>(msg->id, msg->callback);
      } else {
         return actor_handle(msg->actor.lock()).send<timeout_msg>(msg->id, std::move(msg->callback));
      }
   }

   inline auto get_due(const start_timer_msg* msg) {
      return msg->spec.left_match([&](auto const& duration) {
         return msg->issue_time_point + std::chrono::microseconds(duration);
      });
   }
}

timer_set::timer_set() {
}
/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::add_timer(std::unique_ptr<message> msg) -> status_t {
   if(__unlikely(msg == nullptr)) return status_t::null_msg;

   auto start_msg = msg->body<start_timer_msg>();
   if(__unlikely(start_msg == nullptr)) return status_t::failed;

   auto due = get_due(start_msg);
   while(__unlikely(due < std::chrono::steady_clock::now())) {
      if(send_timeout_msg_to_actor(start_msg) != status_t::ok) {
         return status_t::ok;
      }

      if(!start_msg->is_periodic) {
         return status_t::ok;
      } else {
         start_msg->issue_time_point = due;
         due = get_due(start_msg);
      }
   }

   auto iterator = timers_.emplace(due, std::move(msg));
   auto actor_id = start_msg->actor.actor_id();
   actor_indexer_.emplace(actor_id, iterator);

   return status_t::ok;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template<typename PRED, typename OP>
auto timer_set::timer_find_and_modify(int code, intptr_t actor_id, PRED&& pred, OP&& op) -> void {
   auto range = actor_indexer_.equal_range(actor_id);
   auto result = std::find_if(range.first, range.second, std::forward<PRED>(pred));
   if(result != range.second) {
      op(result);
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::remove_timer(intptr_t actor_id, timer_id_t timer_id) -> void {
   timer_find_and_modify(0, actor_id,
       [&](auto const& item) {
          auto&& [_, msg] = *item.second;
          return msg->template body<start_timer_msg>()->id == timer_id;
       },
       [&](auto const& result) {
          timers_.erase(result->second);
          actor_indexer_.erase(result);
       });
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::remove_index(intptr_t actor_id, timers::iterator const& iterator) -> void {
   timer_find_and_modify(1, actor_id,
       [&](auto const& item)      { return item.second == iterator; },
       [this](auto const& result) { actor_indexer_.erase(result);
   });
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::update_index(intptr_t actor_id, timers::iterator const& from, timers::iterator const& to) -> void {
   timer_find_and_modify(2, actor_id,
       [&](auto const& item) { return item.second == from; },
       [&](auto& result)     { result->second = to; });
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::clear_actor_timers(intptr_t actor_id) -> void {
   auto range = actor_indexer_.equal_range(actor_id);
   std::for_each(range.first, range.second, [this](auto const& elem){
      timers_.erase(elem.second);
   });
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

      auto timer_iter = timers_.begin();
      auto&& [due, msg] = *timer_iter;

      if(due > std::chrono::steady_clock::now()) {
         break;
      }

      auto timer_msg = msg->body<start_timer_msg>();

      if(send_timeout_msg_to_actor(timer_msg) != status_t::ok || !timer_msg->is_periodic) {
         remove_index(timer_msg->actor.actor_id(), timer_iter);
         timers_.erase(timer_iter);
      } else {
         timer_msg->issue_time_point = due;
         auto sched_msg = std::move(timer_iter->second);

         timers_.erase(timer_iter);
         auto iterator = timers_.emplace(get_due(timer_msg), std::move(sched_msg));
         update_index(timer_msg->actor.actor_id(), timer_iter, iterator);
      }
   }

   return status_t::ok;
}

/////////////////////////////////////////////////////////////////////////////////////////////
auto timer_set::reset() -> void {
   actor_indexer_.clear();
   timers_.clear();
}

NANO_CAF_NS_END