//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_WORKER_H
#define NANO_CAF_WORKER_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/thread_safe_list.h>
#include <cstddef>
#include <memory>


NANO_CAF_NS_BEGIN

struct resumable;

struct worker : private thread_safe_list {
   auto external_enqueue(resumable *job) noexcept -> void;
   auto launch() noexcept -> void;
   auto stop() noexcept -> void;

   auto wait_done() noexcept -> void;

private:
   auto run() noexcept -> void;
   auto resume_job(resumable*) noexcept -> bool;
   auto cleanup() noexcept -> void;
   auto goto_bed() noexcept -> void;
   auto wakeup_worker() noexcept -> void;

private:
   std::thread thread_{};
   std::mutex lock_{};
   std::condition_variable cv_{};
   bool sleeping{false};
};

NANO_CAF_NS_END

#endif //NANO_CAF_WORKER_H
