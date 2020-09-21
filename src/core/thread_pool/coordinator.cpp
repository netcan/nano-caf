//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/thread_pool/coordinator.h>
#include <nano-caf/core/thread_pool/worker.h>
#include <nano-caf/core/thread_pool/resumable.h>
#include <random>

NANO_CAF_NS_BEGIN

////////////////////////////////////////////////////////////////////
coordinator::coordinator(size_t num_of_workers) noexcept
   : num_of_workers_{num_of_workers}
   , random_{0, num_of_workers-1} {
   launch();
}

////////////////////////////////////////////////////////////////////
auto coordinator::launch() noexcept -> void {
   workers_.reserve(num_of_workers_);
   for(size_t i=0; i<num_of_workers_; ++i) {
      workers_.emplace_back(new worker{*this, i, num_of_workers_ == 1});
   }

   for(auto& worker : workers_) {
      worker->launch();
   }
}

////////////////////////////////////////////////////////////////////
auto coordinator::get_target_worker(resumable& job) -> size_t {
   auto worker_id = job.last_served_worker();
   if(worker_id < workers_.size()) {
      return worker_id;
   }

   if(workers_.size() > 1) {
      std::random_device r;
      std::default_random_engine regen{r()};
      std::uniform_int_distribution<size_t> uniform(0, workers_.size()-1);
      worker_id = uniform(regen);
   } else {
      worker_id = 0;
   }

   job.set_last_served_worker(worker_id);

   return worker_id;
}

////////////////////////////////////////////////////////////////////
auto coordinator::schedule_job(resumable& job) noexcept -> void {
   // always give it to the last served worker to maximum localization
   workers_[get_target_worker(job)]->external_enqueue(&job);
}

////////////////////////////////////////////////////////////////////
auto coordinator::shutdown() noexcept -> void {
   if(shutdown_) return;

   for(auto& worker : workers_) {
      if(worker != nullptr) {
         worker->stop();
      }
   }

   for(auto& worker : workers_) {
      if(worker != nullptr) {
         worker->wait_done();
      }
   }

   sched_jobs_.reserve(workers_.size());

   for(auto& worker : workers_) {
      sched_jobs_.push_back(worker->sched_jobs());
   }

   for(auto& worker : workers_) {
      if(worker != nullptr) {
         delete worker;
         worker = nullptr;
      }
   }

   shutdown_ = true;
}

////////////////////////////////////////////////////////////////////
coordinator::~coordinator() noexcept {
   shutdown();
}

////////////////////////////////////////////////////////////////////
auto coordinator::try_steal(size_t id) noexcept -> resumable* {
   auto victim = random_.gen();
   if(__likely(victim == id)) {
      victim = (victim + 1) % num_of_workers_;
   }

   auto job = workers_[victim]->take_one();
   if(job != nullptr) {
      job->set_last_served_worker(id);
   }
   return job;
}

///////////////////////////////////////////////////////////////////////////
auto coordinator::sched_jobs(size_t worker_id) const noexcept -> size_t {
   if(shutdown_) return sched_jobs_[worker_id];
   return workers_[worker_id]->sched_jobs();
}

NANO_CAF_NS_END