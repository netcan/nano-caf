//
// Created by Darwin Yuan on 2020/7/23.
//

#ifndef NANO_CAF_INTRUSIVE_PTR_H
#define NANO_CAF_INTRUSIVE_PTR_H

#include <nano-caf/nano-caf-ns.h>
#include <algorithm>

NANO_CAF_NS_BEGIN

template<typename T>
struct intrusive_ptr {
   intrusive_ptr() noexcept = default;
   intrusive_ptr(T* ptr, bool add_ref = true) noexcept : ptr_(ptr) {
      if(ptr && add_ref) intrusive_ptr_add_ref(ptr);
   }

   intrusive_ptr(const intrusive_ptr& another) noexcept
      : ptr_(another.ptr_) {
      if(ptr_)
         intrusive_ptr_add_ref(ptr_);
   }

   intrusive_ptr(intrusive_ptr&& another) noexcept
      : ptr_(another.ptr_) {
      another.ptr_ = nullptr;
   }

   ~intrusive_ptr() noexcept {
      if (ptr_)
         intrusive_ptr_release(ptr_);
   }

   intrusive_ptr& operator=(T* ptr) noexcept {
      return operator=(intrusive_ptr{ptr});
   }

   intrusive_ptr& operator=(intrusive_ptr other) noexcept {
      swap(other);
      return *this;
   }

   T* operator->() const noexcept {
      return ptr_;
   }

   T& operator*() const noexcept {
      return *ptr_;
   }

   bool operator!() const noexcept {
      return !ptr_;
   }

   explicit operator bool() const noexcept {
      return ptr_ != nullptr;
   }

   inline friend auto operator==(const intrusive_ptr<T>& x, std::nullptr_t) noexcept -> bool {
      return !x;
   }

   inline friend auto operator==(std::nullptr_t, const intrusive_ptr<T>& x) noexcept -> bool {
      return !x;
   }

   inline friend auto operator!=(const intrusive_ptr<T>& x, std::nullptr_t) noexcept -> bool {
      return static_cast<bool>(x);
   }

   inline friend auto operator!=(std::nullptr_t, const intrusive_ptr<T>& x) noexcept -> bool {
      return static_cast<bool>(x);
   }

   inline friend auto operator==(const intrusive_ptr<T>& x, const T* y) noexcept -> bool {
      return x.ptr_ == y;
   }

   inline friend auto operator==(const T* x, const intrusive_ptr& y) noexcept -> bool {
      return x == y.ptr_;
   }

   inline friend auto operator!=(const intrusive_ptr& x, const T* y) noexcept -> bool {
      return x.ptr_ != y;
   }

   inline friend auto operator!=(const T* x, const intrusive_ptr& y) noexcept -> bool {
      return x != y.ptr_;
   }

   inline friend auto operator==(const intrusive_ptr& x, const intrusive_ptr& y) noexcept -> bool {
      return x.ptr_ == y.ptr_;
   }

   inline friend auto operator!=(const intrusive_ptr& x, const intrusive_ptr& y) noexcept -> bool {
      return x.ptr_ != y.ptr_;
   }
private:
   void swap(intrusive_ptr& other) noexcept {
      std::swap(ptr_, other.ptr_);
   }

private:
   T* ptr_{};
};

NANO_CAF_NS_END

#endif //NANO_CAF_INTRUSIVE_PTR_H
