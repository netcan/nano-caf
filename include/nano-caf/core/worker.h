//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_WORKER_H
#define NANO_CAF_WORKER_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/thread_safe_list.h>
#include <nano-caf/util/disable_copy.h>
#include <cstddef>
#include <memory>

NANO_CAF_NS_BEGIN

struct resumable;

struct coordinator;

struct worker : private thread_safe_list, disable_copy {
   worker(coordinator& coordinator, size_t id) : coordinator_(coordinator), id_(id) {}
   worker(const worker&) = delete;

   auto take_one() noexcept -> resumable*;

   auto external_enqueue(resumable *job) noexcept -> void;
   auto launch() noexcept -> void;
   auto stop() noexcept -> void;

   auto wait_done() noexcept -> void;

   auto id() const noexcept -> size_t {
      return id_;
   }

private:
   auto run() noexcept -> void;
   auto resume_job(resumable*) noexcept -> bool;
   auto cleanup() noexcept -> void;
   auto goto_bed() noexcept -> void;
   auto wakeup_worker() noexcept -> void;
   auto get_a_job() noexcept -> resumable*;

private:
   std::thread thread_{};
   std::mutex lock_{};
   std::condition_variable cv_{};
   coordinator& coordinator_;
   size_t id_;
   size_t strategy_{};
   size_t tried_times_{};
   bool sleeping{false};
};

NANO_CAF_NS_END

#endif //NANO_CAF_WORKER_H
