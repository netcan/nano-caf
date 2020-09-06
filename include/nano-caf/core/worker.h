//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_WORKER_H
#define NANO_CAF_WORKER_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/thread_safe_list.h>
#include <nano-caf/util/disable_copy.h>
#include <nano-caf/core/cache_line_size.h>
#include <nano-caf/core/double_end_list.h>
#include <nano-caf/util/cv_notifier.h>
#include <nano-caf/core/actor/shutdown_notifier.h>
#include <condition_variable>
#include <cstddef>
#include <memory>
#include <mutex>

NANO_CAF_NS_BEGIN

struct resumable;

struct coordinator;

struct
alignas(CACHE_LINE_SIZE)
worker : disable_copy {
   worker(coordinator& coordinator, size_t id)
    : id_(id), coordinator_(coordinator) {}
   worker(const worker&) = delete;

   auto take_one() noexcept -> resumable*;

   auto external_enqueue(resumable *job) noexcept -> void;
   auto launch() noexcept -> void;
   auto stop() noexcept -> void;

   auto wait_done() noexcept -> void;

   auto id() const noexcept -> size_t {
      return id_;
   }

   auto sched_jobs() const -> size_t {
      return sched_jobs_;
   }

private:
   auto run() noexcept -> void;
   auto resume_job(resumable*) noexcept -> bool;
   auto cleanup() noexcept -> void;
   auto goto_bed() noexcept -> void;
   auto get_a_job() noexcept -> resumable*;

private:
   job_list_t job_queue_{};
   cv_notifier cv_{};

   //alignas(CACHE_LINE_SIZE)
   size_t id_{};
   shutdown_notifier shutdown_{};
   coordinator& coordinator_;
   size_t strategy_{};
   size_t tried_times_{};
   size_t sched_jobs_{};

   std::thread thread_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_WORKER_H
