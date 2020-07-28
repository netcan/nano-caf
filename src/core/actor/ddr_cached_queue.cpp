//
// Created by Darwin Yuan on 2020/7/23.
//

#include <nano-caf/core/actor/drr_cached_queue.h>
#include <nano-caf/core/msg/message_element.h>

NANO_CAF_NS_BEGIN

inline auto drr_cached_queue::next() noexcept -> std::unique_ptr<message_element> {
   return task_list::next(deficit_);
}

inline auto drr_cached_queue::flush_cache() noexcept -> void {
   if(!cache_.empty()) task_list::prepend_list(cache_);
}

auto drr_cached_queue::inc_deficit(size_t quota) noexcept -> void {
   if(!task_list::empty()) {
      deficit_ += quota;
   }
}

auto drr_cached_queue::new_round(size_t quota, message_consumer f) noexcept -> new_round_result {
   flush_cache();

   if(task_list::empty()) return {0, false};

   deficit_ += quota;

   size_t consumed = 0;
   for(auto ptr = next(); ptr != nullptr; ptr = next()) {
      switch(task_result result = f(*ptr); result) {
         case task_result::skip:
            cache_.push_back(ptr.release());
            ++deficit_;
            if(task_list::empty()) return {consumed, false};
            break;
         case task_result::resume:
            ++consumed;
            flush_cache();
            if(task_list::empty()) {
               deficit_ = 0;
               return {consumed, false};
            }
            break;
         default:
            ++consumed;
            flush_cache();
            if(task_list::empty()) deficit_ = 0;
            return {consumed, result == task_result::stop_all};
      }
   }

   return {consumed, false};
}

NANO_CAF_NS_END