//
// Created by Darwin Yuan on 2020/8/26.
//

#ifndef NANO_CAF_SHUTDOWN_NOTIFIER_H
#define NANO_CAF_SHUTDOWN_NOTIFIER_H

#include <nano-caf/nano-caf-ns.h>
#include <atomic>

NANO_CAF_NS_BEGIN

struct shutdown_notifier {
   inline auto shutdown_notified() const noexcept -> bool {
      return shutdown_.load(std::memory_order_relaxed);
   }
   inline auto notify_shutdown() -> void {
      shutdown_.store(true, std::memory_order_relaxed);
   }
private:
   std::atomic_bool shutdown_{false};
};

NANO_CAF_NS_END

#endif //NANO_CAF_SHUTDOWN_NOTIFIER_H
