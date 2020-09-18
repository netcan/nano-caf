//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_COORDINATOR_H
#define NANO_CAF_COORDINATOR_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/thread_safe_list.h>
#include <cstddef>
#include <vector>
#include <nano-caf/util/random_generator.h>

NANO_CAF_NS_BEGIN

struct worker;
struct resumable;

struct coordinator {
   explicit coordinator(size_t num_of_workers) noexcept;

   auto shutdown() noexcept -> void;
   auto schedule_job(resumable&) noexcept -> void;
   auto sched_jobs(size_t worker_id) const noexcept -> size_t;

   ~coordinator() noexcept;

private:
   auto launch() noexcept -> void;
   auto try_steal(size_t id) noexcept -> resumable*;
   auto get_target_worker(resumable& job) -> size_t;

   friend struct worker;

private:
   std::vector<worker*> workers_;
   std::vector<size_t> sched_jobs_;
   std::size_t num_of_workers_;
   random_generator random_;
   bool shutdown_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_COORDINATOR_H
