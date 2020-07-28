//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_COORDINATOR_H
#define NANO_CAF_COORDINATOR_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/thread_safe_list.h>

#include <cstddef>
#include <vector>

NANO_CAF_NS_BEGIN

struct worker;
struct resumable;

struct coordinator {
   auto launch(size_t num_of_workers) noexcept -> void;
   auto shutdown() noexcept -> void;
   auto schedule_job(resumable&) noexcept -> void;

   ~coordinator() noexcept;

private:
   auto try_steal(size_t id) noexcept -> resumable*;

   friend struct worker;

private:
   std::vector<worker*> workers_;
   std::atomic_flag lock_{false};
   size_t current_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_COORDINATOR_H
