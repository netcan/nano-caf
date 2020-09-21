//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_FUTURE_OBJECT_H
#define NANO_CAF_FUTURE_OBJECT_H

#include <nano-caf/core/await/promise_done_notifier.h>
#include <type_traits>
#include <utility>
#include <memory>
#include <list>

NANO_CAF_NS_BEGIN namespace detail {

template<typename T>
struct future_object : promise_done_notifier {
   auto set_value(T&& value) -> bool {
      if(present_) return false;
      new (&storage_) T{std::move(value)};
      return present_ = true;
   }

   inline auto ready() const noexcept -> bool {
      return ready_;
   }

   inline operator bool() const noexcept {
      return ready_;
   }

   inline auto present() const noexcept -> bool {
      return present_;
   }

   auto get_value() const noexcept -> const T& {
      return *reinterpret_cast<const T*>(&storage_);
   }

   auto add_notifier(std::shared_ptr<promise_done_notifier> notifier) {
      notifiers_.emplace_back(notifier);
   }

   auto remove_notifier(std::shared_ptr<promise_done_notifier> const& notifier) {
      std::remove_if(notifiers_.begin(), notifiers_.end(), [&](auto const& elem){
         return elem.lock() == notifier;
      });
   }

private:
   auto on_promise_done() noexcept -> void override {
      if(present_ && !ready_) {
         ready_ = true;
         notify_all();
      }
   }

   auto notify_all() {
      for(auto& notifier : notifiers_) {
         auto result = notifier.lock();
         if(result) {
            result->on_promise_done();
         }
      }
      notifiers_.clear();
   }

private:
   std::list<std::weak_ptr<promise_done_notifier>> notifiers_;
   typename std::aligned_storage_t<sizeof(T), alignof(T)> storage_;
   bool present_{false};
   bool ready_{false};
};

} NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_OBJECT_H
