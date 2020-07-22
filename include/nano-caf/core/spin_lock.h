//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_SPIN_LOCK_H
#define NANO_CAF_SPIN_LOCK_H

#include <nano-caf/nano-caf-ns.h>
#include <atomic>
#include <thread>

NANO_CAF_NS_BEGIN

struct spin_lock {
   spin_lock(std::atomic_flag& lock) : lock{lock} {
      while(lock.test_and_set(std::memory_order_acquire)) {
         std::this_thread::yield();
      }
   }

   ~spin_lock() {
      lock.clear(std::memory_order_release);
   }
private:
   std::atomic_flag& lock;
};

NANO_CAF_NS_END

#endif //NANO_CAF_SPIN_LOCK_H
