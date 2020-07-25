//
// Created by Darwin Yuan on 2020/7/23.
//

#ifndef NANO_CAF_RESUMABLE_H
#define NANO_CAF_RESUMABLE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/thread_safe_list.h>
#include <cstddef>

NANO_CAF_NS_BEGIN

struct resumable : list_element {
   enum class result {
      resume_later,
      awaiting_message,
      done,
      shutdown_execution_unit
   };

   virtual auto resume() noexcept -> result = 0;
   virtual ~resumable() noexcept = default;

   inline friend auto intrusive_ptr_add_ref(resumable* ptr) noexcept -> void {
      ptr->intrusive_ptr_add_ref_impl();
   }

   inline friend auto intrusive_ptr_release(resumable* ptr) noexcept -> void {
      ptr->intrusive_ptr_release_impl();
   }

private:
   auto to_value_ptr() -> void* override {
      return reinterpret_cast<void*>(this);
   }

private:
   virtual auto intrusive_ptr_add_ref_impl() noexcept -> void = 0;
   virtual auto intrusive_ptr_release_impl() noexcept -> void = 0;
};

NANO_CAF_NS_END

#endif //NANO_CAF_RESUMABLE_H
