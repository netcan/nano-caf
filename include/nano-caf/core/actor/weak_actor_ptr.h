//
// Created by Darwin Yuan on 2020/10/2.
//

#ifndef NANO_CAF_WEAK_ACTOR_PTR_H
#define NANO_CAF_WEAK_ACTOR_PTR_H

#include <nano-caf/nano-caf-ns.h>
#include <cstddef>

NANO_CAF_NS_BEGIN

struct actor_control_block;
struct intrusive_actor_ptr;

struct weak_actor_ptr {
   weak_actor_ptr() = default;
   weak_actor_ptr(intrusive_actor_ptr& ptr);

   weak_actor_ptr(weak_actor_ptr const& rhs);
   weak_actor_ptr(weak_actor_ptr&& rhs);

   auto operator=(weak_actor_ptr const& rhs) noexcept -> weak_actor_ptr&;
   auto operator=(weak_actor_ptr&& rhs) noexcept -> weak_actor_ptr&;

   ~weak_actor_ptr();

   auto empty() const noexcept -> bool { return ptr_ == nullptr; }
   auto lock() noexcept -> intrusive_actor_ptr;
   auto expired() const noexcept -> bool;
   auto use_count() const noexcept -> std::size_t;

   auto reset() noexcept -> void;

   operator bool() const noexcept { return ptr_ != nullptr; }

   inline friend auto operator==(weak_actor_ptr const& x, std::nullptr_t) noexcept -> bool {
      return !x;
   }

   inline friend auto operator==(std::nullptr_t, weak_actor_ptr const& x) noexcept -> bool {
      return !x;
   }

   inline friend auto operator!=(weak_actor_ptr const& x, std::nullptr_t) noexcept -> bool {
      return static_cast<bool>(x);
   }

   inline friend auto operator!=(std::nullptr_t, weak_actor_ptr const& x) noexcept -> bool {
      return static_cast<bool>(x);
   }

   inline friend auto operator==(weak_actor_ptr const& x, actor_control_block const* y) noexcept -> bool {
      return x.ptr_ == y;
   }

   inline friend auto operator==(actor_control_block const* x, const weak_actor_ptr& y) noexcept -> bool {
      return x == y.ptr_;
   }

   inline friend auto operator!=(weak_actor_ptr const& x, actor_control_block const* y) noexcept -> bool {
      return x.ptr_ != y;
   }

   inline friend auto operator!=(actor_control_block const* x, weak_actor_ptr const& y) noexcept -> bool {
      return x != y.ptr_;
   }

   inline friend auto operator==(weak_actor_ptr const& x, weak_actor_ptr const& y) noexcept -> bool {
      return x.ptr_ == y.ptr_;
   }

   inline friend auto operator!=(weak_actor_ptr const& x, weak_actor_ptr const& y) noexcept -> bool {
      return x.ptr_ != y.ptr_;
   }

private:
   actor_control_block* ptr_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_WEAK_ACTOR_PTR_H
