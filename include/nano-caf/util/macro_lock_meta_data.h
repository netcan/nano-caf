//
// Created by Darwin Yuan on 2020/8/5.
//

#ifndef NANO_CAF_MACRO_LOCK_META_DATA_H
#define NANO_CAF_MACRO_LOCK_META_DATA_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/macro_basic.h>
#include <nano-caf/util/macro_pp_size.h>
#include <nano-caf/util/macro_reflex_call.h>
#include <nano-caf/util/macro_struct.h>
#include <nano-caf/util/macro_meta_common.h>
#include <type_traits>
#include <algorithm>
#include <mutex>
#include <shared_mutex>

///////////////////////////////////////////////////////////////////////////////////////////////
NANO_CAF_NS_BEGIN

namespace lock_meta_data {

   template<typename T, typename = void>
   struct meta_type_trait {
      using type = T;
      using element_type = T;
      using parameter_type = typename meta_data::parameter_type_trait<T>::type;
      using return_type = std::decay_t<T>;
      using value_type = struct {
         mutable std::shared_mutex mutex_;
         T value;
      };

      template<typename F>
      constexpr static bool is_visitable = std::is_invocable_r_v<void, F, parameter_type>;

      template<typename F>
      constexpr static bool is_modifiable = std::is_invocable_r_v<void, F, T&>;

      inline constexpr static auto set(value_type& self, parameter_type value) -> void {
         std::unique_lock lock(self.mutex_);
         self = value;
      }

      inline constexpr static auto get(const value_type& self) -> return_type {
         std::shared_lock lock(self.mutex_);
         return self;
      }

      template<typename F>
      inline static auto visit(parameter_type self, F&& f) -> void {
         std::shared_lock lock(self.mutex_);
         f(self);
      }

      template<typename F>
      inline static auto modify(T& self, F&& f) -> void {
         std::unique_lock lock(self.mutex_);
         f(self);
      }
   };

   template<typename T>
   struct meta_type_trait<T, std::enable_if_t<meta_data::should_pass_by_value<T>>> {
      using type = T;
      using element_type = T;
      using parameter_type = typename meta_data::parameter_type_trait<T>::type;
      using return_type = std::decay_t<T>;
      using value_type = std::atomic<T>;

      template<typename F>
      constexpr static bool is_visitable = std::is_invocable_r_v<void, F, parameter_type>;

      template<typename F>
      constexpr static bool is_modifiable = std::is_invocable_r_v<void, F, T&>;

      inline constexpr static auto set(value_type& self, parameter_type value) -> void {
         self.store(value, std::memory_order_relaxed);
      }

      inline constexpr static auto get(const value_type& self) -> return_type {
         return self.load(std::memory_order_relaxed);
      }

      template<typename F>
      inline static auto visit(value_type& self, F&& f) -> void {
         f(self.load(std::memory_order_relaxed));
      }

      template<typename F>
      inline static auto modify(T& self, F&& f) -> void {
         auto value = self.load(std::memory_order_relaxed);
         f(value);
         self.store(value, std::memory_order_relaxed);
      }
   };

   template<typename C, size_t SIZE>
   struct meta_type_trait<C[SIZE], void> {
      using type = C[SIZE];
      using element_type = C;
      using parameter_type = std::pair<C const*, size_t>;
      using return_type = parameter_type;

      using value_type = struct {
         mutable std::shared_mutex mutex_;
         type data_;
         size_t n_;
      };

      template<typename F>
      constexpr static bool is_visitable = std::is_invocable_r_v<void, F, const C*, size_t>;

      template<typename F>
      constexpr static bool is_modifiable = std::is_invocable_r_v<void, F, C*&, size_t&>;

      inline constexpr static auto set(value_type& self, parameter_type value) -> void {
         std::unique_lock lock(self.mutex_);
         auto [p, size] = value;
         auto total = std::min(SIZE, size);
         self.n_ = total;
         for(size_t i=0; i<total; i++) {
            self.data_[i] = p[i];
         }
      }

      inline constexpr static auto get(const value_type& self) -> return_type {
         std::shared_lock lock(self.mutex_);
         return {self.data_, self.n_};
      }

      template<typename F>
      inline static auto visit(const value_type& self, F&& f) -> void {
         std::shared_lock lock(self.mutex_);
         auto [p, size] = self;
         f(p, size);
      }

      template<typename F>
      inline static auto modify(value_type& self, F&& f) -> void {
         std::unique_lock lock(self.mutex_);
         auto& [p, size] = self;
         f(p, size);
      }
   };

   template<typename C>
   struct meta_type_trait<C[1]> : meta_type_trait<C> {};

   template<typename F>
   constexpr static bool is_none_invokable = std::is_invocable_r_v<void, F>;

   template<size_t N>
   struct meta_flags {
      enum { num_of_bytes = (size_t)((N + 7) / 8) };
      std::atomic<unsigned char> v_[num_of_bytes]{};
   };
}

#define __Lock_Meta_ns NANO_CAF_NS::lock_meta_data
#define __Lock_MeTa(x) __Lock_Meta_ns::meta_type_trait<__CUB_var_type(x)>
#define __Lock_Meta_value_type(x) typename __Lock_MeTa(x)::value_type
#define __Lock_Meta_result(x) typename __Lock_MeTa(x)::return_type
#define __Lock_Meta_para(x) typename __Lock_MeTa(x)::parameter_type
#define __Lock_Meta_elem(x) typename __Lock_MeTa(x)::element_type
#define __Lock_Meta_set_flag(x) __CUB_paste(__CUB_var_name(x), _set_flag)
#define __Lock_Meta_clear(x) __CUB_paste(clear_, __CUB_var_name(x))
///////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_lock_meta_field__(n, x)                                                       \
private:                                                                                    \
   constexpr static size_t  __MeTa_byte(x)       = __Meta_ns::flag_byte(n);                 \
   constexpr static uint8_t __MeTa_mask(x)       = __Meta_ns::flag_mask(n);                 \
   constexpr static uint8_t __MeTa_clear_mask(x) = __Meta_ns::clear_flag_mask(n);           \
private:                                                                                    \
   inline auto __Lock_Meta_set_flag(x)() noexcept -> void {                                 \
      auto flags = __secrete_lk_flags.v_[__MeTa_byte(x)].load(std::memory_order_relaxed);   \
      flags |= __MeTa_mask(x);                                                              \
      __secrete_lk_flags.v_[__MeTa_byte(x)].store(flags, std::memory_order_release);        \
   }                                                                                        \
public:                                                                                     \
   inline auto __Lock_Meta_clear(x)() noexcept -> void {                                    \
      auto flags = __secrete_lk_flags.v_[__MeTa_byte(x)].load(std::memory_order_relaxed);   \
      flags &= __MeTa_clear_mask(x);                                                        \
      __secrete_lk_flags.v_[__MeTa_byte(x)].store(std::memory_order_release);               \
   }                                                                                        \
   inline constexpr auto __CUB_var_name(x)() const noexcept -> __Lock_Meta_result(x) {      \
       return __Lock_MeTa(x)::get(__MeTa_var(x));                                           \
   }                                                                                        \
   inline auto __Meta_present_name(x)() const noexcept -> bool {                            \
       return __MeTa_mask(x) &                                                              \
          __secrete_lk_flags.v_[__MeTa_byte(x)].load(std::memory_order_acquire);            \
   }                                                                                        \
   template<typename F,                                                                     \
            typename = std::enable_if_t<__Lock_MeTa(x)::template is_visitable<F>>>          \
   inline auto __CUB_var_name(x)(F&& f) const noexcept -> void {                            \
       if(__Meta_present_name(x)())                                                         \
          __Lock_MeTa(x)::visit(__MeTa_var(x), std::forward<F>(f));                         \
   }                                                                                        \
   template<typename F_SOME, typename F_NONE,                                               \
            typename = std::enable_if_t<__Lock_MeTa(x)::template is_visitable<F_SOME>>,     \
            typename = std::enable_if_t<__Meta_ns::is_none_invokable<F_NONE>>>              \
   inline auto __CUB_var_name(x)(F_SOME&& f_s, F_NONE&& f_n) const noexcept -> void {       \
       if(__Meta_present_name(x)())                                                         \
          __Lock_MeTa(x)::visit(__MeTa_var(x), std::forward<F_SOME>(f_s));                  \
       else                                                                                 \
          f_n();                                                                            \
   }                                                                                        \
   template<typename F,                                                                     \
            typename = std::enable_if_t<__Lock_MeTa(x)::template is_modifiable<F>>>         \
   inline auto __CUB_var_name(x)(F&& f) noexcept -> void {                                  \
      __Lock_MeTa(x)::modify(__MeTa_var(x), std::forward<F>(f));                            \
      __Lock_Meta_set_flag(x)();                                                            \
   }                                                                                        \
   template<size_t SIZE> inline                                                             \
   auto __CUB_var_name(x)(const __Lock_Meta_elem(x) (&p)[SIZE]) noexcept -> void {          \
      __CUB_var_name(x)({p, SIZE});                                                         \
   }                                                                                        \
   inline auto __CUB_var_name(x)(__Lock_Meta_para(x) p) noexcept -> void {                  \
      __Lock_MeTa(x)::set(__MeTa_var(x), p);                                                \
      __Lock_Meta_set_flag(x)();                                                            \
   }                                                                                        \
private:                                                                                    \
   __Lock_Meta_value_type(x) __MeTa_var(x);                                                 \


#define __CUB_lock_meta_data(...)                                                \
__CUB_all_fields__(__CUB_lock_meta_field__, __VA_ARGS__)                         \
private:                                                                         \
   __Lock_Meta_ns::meta_flags<__CUB_pp_size(__VA_ARGS__)> __secrete_lk_flags

NANO_CAF_NS_END

#endif //NANO_CAF_MACRO_LOCK_META_DATA_H
