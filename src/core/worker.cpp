//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/worker.h>
#include <nano-caf/core/resumable.h>
#include <nano-caf/core/actor/actor_control_block.h>
#include <nano-caf/core/coordinator.h>
#include <iostream>

NANO_CAF_NS_BEGIN

////////////////////////////////////////////////////////////////////
auto worker::take_one() noexcept -> resumable* {
   return thread_safe_list::pop_front<resumable>();
}

////////////////////////////////////////////////////////////////////
auto worker::external_enqueue(resumable* job) noexcept -> void {
   intrusive_ptr_add_ref(job);
   thread_safe_list::push_back(job);
   wakeup_worker();
}

////////////////////////////////////////////////////////////////////
auto worker::wait_done() noexcept -> void {
   thread_.join();
   cleanup();
}

////////////////////////////////////////////////////////////////////
auto worker::stop() noexcept -> void {
   struct shutdown : resumable {
      auto resume() noexcept -> result override {
         return result::shutdown_execution_unit;
      }

      auto intrusive_ptr_add_ref_impl() noexcept -> void override {}
      auto intrusive_ptr_release_impl() noexcept -> void override {
         delete this;
      }
   };

   cmd_queue_.push_back(new shutdown{});
   wakeup_worker();
}

////////////////////////////////////////////////////////////////////
using timespan = std::chrono::duration<int64_t, std::nano>;

constexpr timespan sleep_durations[3] = {
   timespan{1'000'000'000},
   timespan{1'000'000'000},
   timespan{1'000'000'000},
};

constexpr size_t try_times[3] = {
   100,
   10,
   1
};

////////////////////////////////////////////////////////////////////
auto worker::goto_bed() noexcept -> void {
   if(strategy_ < 2 && tried_times_++ >= try_times[strategy_]) {
      ++strategy_;
   }
   goto_bed_();
}

////////////////////////////////////////////////////////////////////
auto worker::goto_bed_() noexcept -> void {
   std::unique_lock<std::mutex> guard(lock_);
   sleeping = true;
   cv_.wait_for(guard, sleep_durations[strategy_],
                [&] { return !thread_safe_list::empty(); });
   sleeping = false;
}
////////////////////////////////////////////////////////////////////
auto worker::wakeup_worker() noexcept -> void {
   std::unique_lock<std::mutex> guard(lock_);
   if (sleeping && (!thread_safe_list::empty() || !cmd_queue_.empty()))
      cv_.notify_one();
}

////////////////////////////////////////////////////////////////////
auto worker::get_a_job() noexcept -> resumable* {
   auto job = cmd_queue_.pop_front<resumable>();
   if(job != nullptr) return job;

   job = thread_safe_list::pop_front<resumable>();
   if(job != nullptr) return job;

   return job;
   //return coordinator_.try_steal(id_);
}

////////////////////////////////////////////////////////////////////
auto worker::run() noexcept -> void {
   while (1) {
      auto job = get_a_job();
      if(job != nullptr) {
         if(!resume_job(job)) return;
         strategy_ = 0;
         tried_times_ = 0;
      } else {
         goto_bed();
      }
   }
}

////////////////////////////////////////////////////////////////////
auto worker::cleanup() noexcept -> void {
   while (1) {
      auto job = thread_safe_list::pop_front<resumable>();
      if(job == nullptr) {
         break;
      }
   }
}

////////////////////////////////////////////////////////////////////
auto worker::resume_job(resumable* job) noexcept -> bool {

   switch(job->resume()) {
      case resumable::result::resume_later:
         thread_safe_list::push_back(job);
         break;
      case resumable::result::shutdown_execution_unit:
         return false;
      case resumable::result::done:
      case resumable::result::awaiting_message:
      default:
         intrusive_ptr_release(job);
         break;
   }

   return true;
}

////////////////////////////////////////////////////////////////////
auto worker::launch() noexcept -> void {
   thread_ = std::thread{[this] {
      run();
   }};
}

NANO_CAF_NS_END