//
// Created by Darwin Yuan on 2020/8/5.
//

#ifndef NANO_CAF_MACRO_META_DATA_H
#define NANO_CAF_MACRO_META_DATA_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/macro_basic.h>
#include <nano-caf/util/macro_pp_size.h>
#include <nano-caf/util/macro_reflex_call.h>
#include <nano-caf/util/macro_struct.h>
#include <type_traits>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////////////////////
NANO_CAF_NS_BEGIN

namespace meta_data {

   template<typename T, typename = void>
   struct parameter_type_trait {
      using type = std::add_lvalue_reference_t<std::add_const_t<std::decay_t<T>>>;
   };

   template<typename T>
   constexpr bool should_pass_by_value = !std::is_array_v<T> &&
      (std::is_arithmetic_v<T> || std::is_pointer_v<T>) && sizeof(T) <= sizeof(void*);

   template<typename T>
   struct parameter_type_trait<T, std::enable_if_t<should_pass_by_value<std::decay_t<T>>>> {
      using type = std::decay_t<T>;
   };

   template<typename T>
   struct ro_meta_type_trait {
      using type = T;
      using element_type = T;
      using parameter_type = typename parameter_type_trait<T>::type;
      using return_type = parameter_type;
      using value_type = T;

      template<typename F>
      constexpr static bool is_visitable = std::is_invocable_r_v<void, F, value_type>;

      template<typename F>
      constexpr static bool is_modifiable = std::is_invocable_r_v<void, F, value_type&>;

      inline constexpr static auto set(value_type& self, parameter_type value) -> void {
         self = value;
      }

      inline constexpr static auto get(const value_type& self) -> return_type {
         return self;
      }

      template<typename F>
      inline constexpr static auto visit(parameter_type self, F&& f) -> void {
         f(self);
      }

      template<typename F>
      inline static auto modify(T& self, F&& f) -> void {
         f(self);
      }
   };

   template<typename C, size_t SIZE>
   struct ro_meta_type_trait<C[SIZE]> {
      using type = C[SIZE];
      using element_type = C;
      using parameter_type = std::pair<C const*, size_t>;
      using return_type = parameter_type;

      using value_type = struct {
         type data_;
         size_t n_;
      };

      template<typename F>
      constexpr static bool is_visitable = std::is_invocable_r_v<void, F, const C*, size_t>;

      template<typename F>
      constexpr static bool is_modifiable = std::is_invocable_r_v<void, F, C*&, size_t&>;

      inline constexpr static auto set(value_type& self, parameter_type value) -> void {
         auto [p, size] = value;
         auto total = std::min(SIZE, size);
         self.n_ = total;
         for(size_t i=0; i<total; i++) {
            self.data_[i] = p[i];
         }
      }

      inline constexpr static auto get(const value_type& self) -> return_type {
         return {self.data_, self.n_};
      }

      template<typename F>
      inline constexpr static auto visit(const value_type& self, F&& f) -> void {
         auto [p, size] = self;
         f(p, size);
      }

      template<typename F>
      inline static auto modify(value_type& self, F&& f) -> void {
         auto& [p, size] = self;
         f(p, size);
      }
   };

   template<typename C>
   struct ro_meta_type_trait<C[1]> : ro_meta_type_trait<C> {};

   template<typename F>
   constexpr static bool is_none_invokable = std::is_invocable_r_v<void, F>;

   template<size_t N>
   struct fo_meta_flags {
      enum { num_of_bytes = (size_t)((N + 7) / 8) };
      unsigned char flags_[num_of_bytes];
   };

   static constexpr auto flag_byte(size_t n) -> size_t {
      return size_t(n / 8);
   }

   static constexpr auto flag_mask(size_t n) -> uint8_t {
      return uint8_t(n % 8);
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////
#define __RO_MeTa(x) meta_data::ro_meta_type_trait<__CUB_var_type(x)>
#define __MeTa_var(x) __CUB_paste(__CUB_var_name(x), _)
#define __MeTa_byte(x) __CUB_paste(__CUB_var_name(x), _byte)
#define __MeTa_mask(x) __CUB_paste(__CUB_var_name(x), _mask)
#define __RO_Meta_value_type(x) typename __RO_MeTa(x)::value_type
#define __RO_Meta_result(x) typename __RO_MeTa(x)::return_type
#define __RO_Meta_para(x) typename __RO_MeTa(x)::parameter_type
#define __Meta_present_name(x) __CUB_paste(__CUB_var_name(x), _present)
#define __RO_Meta_elem(x) typename __RO_MeTa(x)::element_type

#define __Meta_ns NANO_CAF_NS::meta_data
///////////////////////////////////////////////////////////////////////////////////////////////
#define __CUB_no_lock_meta_field__(n, x, set_visibility)                               \
private:                                                                              \
   constexpr static size_t  __MeTa_byte(x) = __Meta_ns::flag_byte(n);                 \
   constexpr static uint8_t __MeTa_mask(x) = __Meta_ns::flag_mask(n);                 \
public:                                                                               \
   inline constexpr auto __CUB_var_name(x)() const noexcept -> __RO_Meta_result(x) {  \
       return __RO_MeTa(x)::get(__MeTa_var(x));                                       \
   }                                                                                  \
   template<typename F,                                                               \
            typename = std::enable_if_t<__RO_MeTa(x)::template is_visitable<F>>>      \
   inline constexpr auto __CUB_var_name(x)(F&& f) const noexcept -> void {            \
       if(__Meta_present_name(x)())                                                   \
          __RO_MeTa(x)::visit(__MeTa_var(x), std::forward<F>(f));                     \
   }                                                                                  \
   template<typename F_SOME, typename F_NONE,                                         \
            typename = std::enable_if_t<__RO_MeTa(x)::template is_visitable<F_SOME>>, \
            typename = std::enable_if_t<__Meta_ns::is_none_invokable<F_NONE>>>        \
   inline constexpr                                                                   \
   auto __CUB_var_name(x)(F_SOME&& f_some, F_NONE&& f_none) const noexcept -> void {  \
       if(__Meta_present_name(x)())                                                   \
          __RO_MeTa(x)::visit(__MeTa_var(x), std::forward<F_SOME>(f_some));           \
       else                                                                           \
          f_none();                                                                   \
   }                                                                                  \
   inline constexpr auto __Meta_present_name(x)() const noexcept -> bool {            \
       return __secrete_flags.flags_[__MeTa_byte(x)] & __MeTa_mask(x);                \
   }                                                                                  \
set_visibility:                                                                       \
   template<typename F,                                                               \
            typename = std::enable_if_t<__RO_MeTa(x)::template is_modifiable<F>>>     \
   inline auto __CUB_var_name(x)(F&& f) noexcept -> void {                            \
      __RO_MeTa(x)::modify(__MeTa_var(x), std::forward<F>(f));                        \
      __secrete_flags.flags_[__MeTa_byte(x)] |= __MeTa_mask(x);                       \
   }                                                                                  \
   template<size_t SIZE> inline                                                       \
   auto __CUB_var_name(x)(const __RO_Meta_elem(x) (&p)[SIZE]) noexcept -> void {      \
      __CUB_var_name(x)({p, SIZE});                                                   \
   }                                                                                  \
   inline auto __CUB_var_name(x)(__RO_Meta_para(x) p) noexcept -> void {              \
      __RO_MeTa(x)::set(__MeTa_var(x), p);                                            \
      __secrete_flags.flags_[__MeTa_byte(x)] |= __MeTa_mask(x);                       \
   }                                                                                  \
private:                                                                              \
   __RO_Meta_value_type(x) __MeTa_var(x);

///////////////////////////////////////////////////////////////////////////////////////
#define __CUB_ro_field__(n, x) __CUB_no_lock_meta_field__(n, x, protected)

///////////////////////////////////////////////////////////////////////////////////////
#define __CUB_ro_fields(...)                                                \
__CUB_all_fields__(__CUB_ro_field__, __VA_ARGS__)                           \
private:                                                                    \
   __Meta_ns::fo_meta_flags<__CUB_pp_size(__VA_ARGS__)> __secrete_flags

NANO_CAF_NS_END

#endif //NANO_CAF_MACRO_META_DATA_H
