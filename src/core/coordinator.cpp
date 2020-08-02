//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/coordinator.h>
#include <nano-caf/core/worker.h>
#include <nano-caf/core/resumable.h>
#include <random>

NANO_CAF_NS_BEGIN

////////////////////////////////////////////////////////////////////
auto coordinator::launch(size_t num_of_workers) noexcept -> void {
   workers_.reserve(num_of_workers);
   for(size_t i=0; i<num_of_workers; ++i) {
      workers_.emplace_back(new worker(*this, i));
   }

   for(auto& worker : workers_) {
      worker->launch();
   }
}

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
   if(workers_.size() == 1) {
      return nullptr;
   }

   auto try_times = workers_.size() - 1;

   std::random_device r;
   std::default_random_engine regen{r()};
   std::uniform_int_distribution<size_t> uniform(0, try_times);

   for(auto i = 0; i < try_times; ++i) {
      auto victim = uniform(regen);
      if(victim != id) {
         auto job = workers_[victim]->take_one();
         if(job != nullptr) {
            job->set_last_served_worker(id);
         }
         return job;
      }
   }

   return nullptr;
}

////////////////////////////////////////////////////////////////////
auto coordinator::sched_jobs(size_t worker_id) const noexcept -> size_t {
   if(shutdown_) return sched_jobs_[worker_id];
   return workers_[worker_id]->sched_jobs();
}

NANO_CAF_NS_END