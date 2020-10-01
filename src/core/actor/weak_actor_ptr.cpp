//
// Created by Darwin Yuan on 2020/10/2.
//

#include <nano-caf/core/actor/weak_actor_ptr.h>
#include <nano-caf/core/actor/intrusive_actor_ptr.h>
#include <nano-caf/core/actor/actor_control_block.h>

NANO_CAF_NS_BEGIN

weak_actor_ptr::weak_actor_ptr(intrusive_actor_ptr& ptr)
   : ptr_{ptr.raw()} {
   if(ptr_ != nullptr) {
      intrusive_ptr_add_weak_ref(ptr_);
   }
}

auto weak_actor_ptr::reset() noexcept -> void {
   if(ptr_ != nullptr) {
      intrusive_ptr_release_weak(ptr_);
      ptr_ = {};
   }
}

weak_actor_ptr::weak_actor_ptr(weak_actor_ptr const& rhs) : ptr_ {rhs.ptr_} {
   if(ptr_ != nullptr) {
      intrusive_ptr_add_weak_ref(ptr_);
   }
}

weak_actor_ptr::weak_actor_ptr(weak_actor_ptr&& rhs) : ptr_{rhs.ptr_}{
   rhs.ptr_ = nullptr;
}

auto weak_actor_ptr::operator=(weak_actor_ptr const& rhs) noexcept -> weak_actor_ptr& {
   reset();
   ptr_ = rhs.ptr_;
   if(ptr_ != nullptr) {
      intrusive_ptr_add_weak_ref(ptr_);
   }
   return *this;
}

auto weak_actor_ptr::operator=(weak_actor_ptr&& rhs) noexcept -> weak_actor_ptr& {
   rhs.ptr_ = std::exchange(ptr_, rhs.ptr_);
   return *this;
}

weak_actor_ptr::~weak_actor_ptr() {
  reset();
}

auto weak_actor_ptr::lock() noexcept -> intrusive_actor_ptr {
   if(ptr_ != nullptr) {
      return intrusive_ptr_upgrade_weak(ptr_);
   } else {
      return {};
   }
}

auto weak_actor_ptr::expired() const noexcept -> bool {
   return ptr_ == nullptr || ptr_->use_count() == 0;
}

auto weak_actor_ptr::use_count() const noexcept -> std::size_t {
   return ptr_ == nullptr ? 0 : ptr_->use_count();
}

NANO_CAF_NS_END