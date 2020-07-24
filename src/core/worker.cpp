//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/worker.h>
#include <nano-caf/core/resumable.h>
#include <nano-caf/core/actor/actor_control_block.h>

NANO_CAF_NS_BEGIN

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

      auto intrusive_ptr_add_ref_impl() -> void override {}
      auto intrusive_ptr_release_impl() -> void override {
         delete this;
      }
   };

   thread_safe_list::push_front(new shutdown{});
   wakeup_worker();
}

using timespan = std::chrono::duration<int64_t, std::nano>;

////////////////////////////////////////////////////////////////////
auto worker::goto_bed() noexcept -> void {
   std::unique_lock<std::mutex> guard(lock_);
   sleeping = true;
   cv_.wait(guard,[&] { return !thread_safe_list::empty(); });
   sleeping = false;
}

////////////////////////////////////////////////////////////////////
auto worker::wakeup_worker() noexcept -> void {
   std::unique_lock<std::mutex> guard(lock_);
   if (sleeping && !thread_safe_list::empty())
      cv_.notify_one();
}

////////////////////////////////////////////////////////////////////
auto worker::run() noexcept -> void {
   while (1) {
      auto job = thread_safe_list::pop_front<resumable>();
      if(job == nullptr) {
         goto_bed();
      }
      else if(!resume_job(job)) {
         return;
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