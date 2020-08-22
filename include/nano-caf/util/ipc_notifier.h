//
// Created by Darwin Yuan on 2020/8/22.
//

#ifndef NANO_CAF_IPC_NOTIFIER_H
#define NANO_CAF_IPC_NOTIFIER_H

#include <mutex>
#include <condition_variable>
#include <chrono>

struct ipc_notifier {
   template<typename F>
   auto wait(F&& f) {
      std::unique_lock lock(mutex_);
      sleeping_ = true;
      cv_.wait(lock, std::forward<F>(f));
      sleeping_ = false;
   }

   template<class Rep, class Period, typename F>
   auto wait_for(std::chrono::duration<Rep, Period> const& duration, F&& f) {
      std::unique_lock lock(mutex_);
      sleeping_ = true;
      auto result = cv_.wait_for(lock, duration, std::forward<F>(f));
      sleeping_ = false;
      return result;
   }

   template<class Clock, class Duration, typename F>
   auto wait_until(std::chrono::time_point<Clock, Duration> const& point, F&& f) {
      std::unique_lock lock(mutex_);
      sleeping_ = true;
      auto result = cv_.wait_until(lock, point, std::forward<F>(f));
      sleeping_ = false;
      return result;
   }

   template<class Clock, class Duration>
   auto wait_until(std::chrono::time_point<Clock, Duration> const& point) {
      std::unique_lock lock(mutex_);
      sleeping_ = true;
      auto result = cv_.wait_until(lock, point);
      sleeping_ = false;
      return result;
   }

   auto wake_up() {
      std::unique_lock lock(mutex_);
      if(sleeping_) {
         cv_.notify_one();
      }
   }

private:
   std::mutex mutex_{};
   std::condition_variable cv_{};
   bool sleeping_{false};
};

#endif //NANO_CAF_IPC_NOTIFIER_H
