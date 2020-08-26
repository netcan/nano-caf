//
// Created by Darwin Yuan on 2020/8/22.
//

#include <nano-caf/core/timer/timer_set.h>
#include <nano-caf/util/likely.h>
#include <nano-caf/core/actor/actor_handle.h>
#include <spdlog/spdlog.h>
#include <nano-caf/core/actor/shutdown_notifier.h>

NANO_CAF_NS_BEGIN

auto timer_set::add_timer(std::unique_ptr<message> msg) -> status_t {
   if(__unlikely(msg == nullptr)) return status_t::null_msg;

   auto start_msg = msg->body<start_timer_msg>();
   if(__unlikely(start_msg == nullptr)) return status_t::failed;

   auto due = start_msg->spec.left_match([&](auto const& duration) {
      return start_msg->issue_time_point + std::chrono::microseconds(duration);
   });

   if(due < std::chrono::system_clock::now()) {
      actor_handle(start_msg->actor).send<timeout_msg>(start_msg->id, start_msg->callback);
      if(!start_msg->is_periodic) {
         return status_t::ok;
      }
   }

   auto iterator = timers_.emplace(due, std::move(msg));
   auto actor_id = start_msg->actor.actor_id();
   actor_indexer_.emplace(actor_id, iterator);

   return status_t::ok;
}

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

auto timer_set::clear_actor_timers(intptr_t actor_id) -> void {
   auto range = actor_indexer_.equal_range(actor_id);
   for(auto i = range.first; i != range.second; ++i) {
      timers_.erase(i->second);
   }
   actor_indexer_.erase(range.first, range.second);
}

auto timer_set::on_timeout(const shutdown_notifier& shutdown) -> void {
   while(!timers_.empty()) {
      if(__unlikely(shutdown.shutdown_notified())) break;

      auto timer = timers_.begin();
      if(timer->first > std::chrono::system_clock::now()) {
         break;
      }

      auto msg = timer->second->body<start_timer_msg>();
      actor_handle(msg->actor).send<timeout_msg>(msg->id, msg->callback);

      actor_indexer_.erase(msg->actor.actor_id());

      if(msg->is_periodic) {
         msg->issue_time_point = timer->first;
         auto sched_msg = std::move(timer->second);
         timers_.erase(timer);
         add_timer(std::move(sched_msg));
      } else {
         timers_.erase(timer);
      }
   }
}

auto timer_set::reset() -> void {
   actor_indexer_.clear();
   timers_.clear();
}

NANO_CAF_NS_END