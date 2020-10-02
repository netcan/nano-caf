//
// Created by Darwin Yuan on 2020/10/2.
//
#include <nano-caf/core/await/detail/future_object_base.h>

NANO_CAF_NS_BEGIN namespace detail {

auto future_object_base::set_fail_handler(failure_handler&& handler) noexcept -> void {
   if(f_on_fail_) return;
   if(!ready_) { f_on_fail_ = std::move(handler); }
   else if(!present_) { handler(failure_); }
}

auto future_object_base::add_observer(observer_type observer) noexcept -> void {
   if(ready_) { notify_observer_(observer); }
   else { observers_.emplace_back(std::move(observer)); }
}

auto future_object_base::commit() noexcept -> void {
   if (ready_ ) return;
   ready_ = true;
   if(!present_ && static_cast<bool>(f_on_fail_)) { f_on_fail_(failure_); }
   notify_observers();
   destroy();
}

auto future_object_base::deregister_observer(future_observer* observer, status_t cause) noexcept -> void {
   auto result = std::find(observers_.begin(), observers_.end(), observer);
   if(result != observers_.end()) {
      observers_.erase(result);
      if(observers_.empty()) { cancel(cause); }
   }
}

auto future_object_base::on_fail(status_t cause) noexcept -> void {
   if (present_ || ready_) return;
   failure_ = cause;
}

auto future_object_base::destroy() noexcept -> void {
   if(!registered_) return;
   context_.remove_future(this);
   registered_ = false;
}

auto future_object_base::cancel_observers(status_t cause) noexcept -> void {
   for (auto &observer: observers_) {
      cancel_observer(observer, cause);
   }
   observers_.clear();
}

auto future_object_base::notify_observers() noexcept -> void {
   for (auto &observer: observers_) { notify_observer_(observer); }
   observers_.clear();
}

auto future_object_base::do_cancel(status_t cause) noexcept -> void {
   if(ready_) return;
   ready_ = true;
   if(f_on_fail_) f_on_fail_(cause);
   cancel_observers(cause);
   destroy();
}

auto future_object_base::cancel_observer(observer_type &observer, status_t cause) noexcept -> void {
   observer->on_future_fail(cause);
}

auto future_object_base::notify_observer_(observer_type &observer) noexcept -> void {
   if(present_) observer->on_future_ready();
   else observer->on_future_fail(failure_);
}

} NANO_CAF_NS_END

