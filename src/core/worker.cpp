//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/worker.h>
#include <nano-caf/core/resumable.h>
#include <nano-caf/core/actor/actor_control_block.h>

NANO_CAF_NS_BEGIN

auto worker::external_enqueue(resumable* job) -> void {
   intrusive_ptr_add_ref(job);
   thread_safe_list::push_back(job);
}

using timespan = std::chrono::duration<int64_t, std::nano>;

auto worker::run() -> void {
   timespan sleep_duration{10000};

   bool notimeout = true;
   while (1) {
      auto job = thread_safe_list::pop_front<resumable>();
      if(job) {
         resume_job(job);
      } else {
            std::unique_lock<std::mutex> guard(lock_);
            sleeping = true;
            if (!cv_.wait_for(guard, sleep_duration,
                             [&] { return !thread_safe_list::empty(); }))
               notimeout = false;
            sleeping = false;
      }
   }
}

auto worker::resume_job(resumable* job) -> void {
   switch(job->resume()) {
      case resumable::result::resume_later:
         thread_safe_list::push_back(job);
         break;
      default:
         intrusive_ptr_release(job);
         break;
   }
}

auto worker::launch() -> void {
   std::thread{
      [this] {
         run();
      }
   };
}

NANO_CAF_NS_END