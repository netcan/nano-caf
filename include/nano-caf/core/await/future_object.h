//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_FUTURE_OBJECT_H
#define NANO_CAF_FUTURE_OBJECT_H

#include <nano-caf/core/await/promise_done_notifier.h>
#include <nano-caf/core/await/future_done_notifier.h>
#include <nano-caf/util/caf_log.h>
#include <type_traits>
#include <utility>
#include <memory>
#include <list>

NANO_CAF_NS_BEGIN namespace detail {

template<typename T>
struct future_object_base : promise_done_notifier {
   auto ready() const noexcept -> bool {
      return ready_;
   }

   auto present() const noexcept -> bool {
      return present_;
   }

   auto add_notifier(std::shared_ptr<future_done_notifier> notifier) {
      notifiers_.emplace_back(notifier);
   }

   auto remove_notifier(std::shared_ptr<future_done_notifier> const& notifier) {
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
            result->on_future_done();
         }
      }
      notifiers_.clear();
   }

private:
   std::list<std::weak_ptr<future_done_notifier>> notifiers_;
   bool ready_{false};

protected:
   bool present_{false};
};

template<typename T>
struct future_object : future_object_base<T> {
   using super = future_object_base<T>;
   auto set_value(T&& value) -> bool {
      if(super::present_) return false;
      new (&storage_) T{std::move(value)};
      return super::present_ = true;
   }

   auto get_value() const noexcept -> const T& {
      return *reinterpret_cast<const T*>(&storage_);
   }

private:
   typename std::aligned_storage_t<sizeof(T), alignof(T)> storage_;
};

template<>
struct future_object<void> : future_object_base<void> {
   using super = future_object_base<void>;
   auto set_value() -> bool {
      if(super::present_) return false;
      return super::present_ = true;
   }
};

} NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_OBJECT_H
