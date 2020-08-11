
#ifndef __CUB_AGGREGATE_FIELDS_TYPE_H__
#define __CUB_AGGREGATE_FIELDS_TYPE_H__

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/type_list.h>
#include <type_traits>

NANO_CAF_NS_BEGIN

namespace detail {
template<size_t N, typename T>
class aggregate_fields_type;

template<typename T>
class aggregate_fields_type<0, T> {
   using type = type_list<>;
   template <typename F>
   static auto call(const T&, F&& f) {{
      return f();
   }}
};


template<typename T>
class aggregate_fields_type<1, T> { 
    constexpr static auto deduce_type() {
        auto [a1] = T{};
        return type_list<decltype(a1)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(const T& obj, F&& f) {
        auto [a1] = obj;
        return f(a1);
    }
};

template<typename T>
class aggregate_fields_type<2, T> { 
    constexpr static auto deduce_type() {
        auto [a1,a2] = T{};
        return type_list<decltype(a1),decltype(a2)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(const T& obj, F&& f) {
        auto [a1,a2] = obj;
        return f(a1,a2);
    }
};

template<typename T>
class aggregate_fields_type<3, T> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(const T& obj, F&& f) {
        auto [a1,a2,a3] = obj;
        return f(a1,a2,a3);
    }
};

template<typename T>
class aggregate_fields_type<4, T> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(const T& obj, F&& f) {
        auto [a1,a2,a3,a4] = obj;
        return f(a1,a2,a3,a4);
    }
};

template<typename T>
class aggregate_fields_type<5, T> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(const T& obj, F&& f) {
        auto [a1,a2,a3,a4,a5] = obj;
        return f(a1,a2,a3,a4,a5);
    }
};

template<typename T>
class aggregate_fields_type<6, T> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(const T& obj, F&& f) {
        auto [a1,a2,a3,a4,a5,a6] = obj;
        return f(a1,a2,a3,a4,a5,a6);
    }
};

template<typename T>
class aggregate_fields_type<7, T> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(const T& obj, F&& f) {
        auto [a1,a2,a3,a4,a5,a6,a7] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7);
    }
};

template<typename T>
class aggregate_fields_type<8, T> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(const T& obj, F&& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8);
    }
};

template<typename T>
class aggregate_fields_type<9, T> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(const T& obj, F&& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9);
    }
};

template<typename T>
class aggregate_fields_type<10, T> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10
              ] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(const T& obj, F&& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10
              ] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10
              );
    }
};

}

NANO_CAF_NS_END

#endif
