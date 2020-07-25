//
// Created by Darwin Yuan on 2020/7/24.
//

#include <nano-caf/core/coordinator.h>
#include <nano-caf/core/worker.h>
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

////////////////////////////////////////////////////////////////////
auto coordinator::schedule_job(resumable& job) noexcept -> void {
   spin_lock lock(lock_);
   workers_[current_]->external_enqueue(&job);
   current_ = (++current_) % workers_.size();
}

////////////////////////////////////////////////////////////////////
auto coordinator::stop() noexcept -> void {
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

   for(auto& worker : workers_) {
      if(worker != nullptr) {
         delete worker;
         worker = nullptr;
      }
   }
}

////////////////////////////////////////////////////////////////////
coordinator::~coordinator() noexcept {
   stop();
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
            return job;
         }
      }
   }

   return nullptr;
}


NANO_CAF_NS_END