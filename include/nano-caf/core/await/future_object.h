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
struct future_object;

template<typename T>
using future_object_sp = std::shared_ptr<future_object<T>>;

template<typename T>
using future_launcher = std::function<status_t (future_object_sp<T>)>;

template<typename T>
struct future_object_base
   : std::enable_shared_from_this<future_object<T>>
   , promise_done_notifier {
   using super = std::enable_shared_from_this<future_object<T>>;
   explicit future_object_base(future_launcher<T>&& launcher)
      : launcher_{std::move(launcher)}
   {}

   auto ready() const noexcept -> bool {
      return ready_;
   }

   auto present() const noexcept -> bool {
      return present_;
   }

   auto add_notifier(std::shared_ptr<future_done_notifier> notifier) {
      try_launch();
      if(!present_ && ready_) {
         notifier->on_future_fail(failure_);;
      } else {
         notifiers_.emplace_back(notifier);
      }
   }

   auto on_value_present() noexcept -> void {
      present_ = true;
   }

private:
   auto try_launch() noexcept -> void {
      if(notifiers_.size() == 0) {
         auto result = launcher_(super::shared_from_this());
         if(result != status_t::ok) {
            ready_ = true;
            failure_ = result;
         }
      }
   }

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
   future_launcher<T> launcher_;
   status_t failure_;
   bool launched_{false};
   bool ready_{false};
   bool present_{false};
};

template<typename T>
struct future_object : future_object_base<T> {
   using super = future_object_base<T>;
   using super::super;

   auto set_value(T&& value) -> bool {
      if(super::present()) return false;
      new (&storage_) T{std::move(value)};
      super::on_value_present();
      return true;
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
   using super::super;
   auto set_value() -> bool {
      if(super::present()) return false;
      on_value_present();
      return true;
   }
};

} NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_OBJECT_H
