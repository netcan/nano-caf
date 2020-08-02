//
// Created by Darwin Yuan on 2020/8/2.
//

#include <nano-caf/core/actor/drr_queue.h>
#include <nano-caf/core/msg/message.h>

NANO_CAF_NS_BEGIN

inline auto drr_queue::next() noexcept -> std::unique_ptr<message> {
   return task_list::next(deficit_);
}


auto drr_queue::inc_deficit(size_t quota) noexcept -> void {
   if(!task_list::empty()) {
      deficit_ += quota;
   }
}

auto drr_queue::new_round(size_t quota, message_consumer f) noexcept -> new_round_result {
   if(task_list::empty()) return {0, false};

   deficit_ += quota;

   size_t consumed = 0;
   for(auto ptr = next(); ptr != nullptr; ptr = next()) {
      switch(task_result result = f(*ptr); result) {
         case task_result::skip:
            ++deficit_;
            if(task_list::empty()) return {consumed, false};
            break;
         case task_result::resume:
            ++consumed;
            if(task_list::empty()) {
               deficit_ = 0;
               return {consumed, false};
            }
            break;
         default:
            ++consumed;
            if(task_list::empty()) deficit_ = 0;
            return {consumed, result == task_result::done};
      }
   }

   return {consumed, false};
}

NANO_CAF_NS_END