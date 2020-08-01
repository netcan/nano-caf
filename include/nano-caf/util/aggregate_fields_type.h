
#ifndef __CUB_AGGREGATE_FIELDS_TYPE_H__
#define __CUB_AGGREGATE_FIELDS_TYPE_H__

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/type_list.h>
#include <type_traits>

NANO_CAF_NS_BEGIN

namespace detail {
template<size_t N, typename T, typename = void>
struct aggregate_fields_type;

template<typename T>
struct aggregate_fields_type<0, T, std::enable_if_t<std::is_aggregate_v<T>>> {
   using type = type_list<>;
};


template<typename T>
class aggregate_fields_type<1, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1] = T{};
        return type_list<decltype(a1)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1] = obj;
        return f(a1);
    }
};

template<typename T>
class aggregate_fields_type<2, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2] = T{};
        return type_list<decltype(a1),decltype(a2)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2] = obj;
        return f(a1,a2);
    }
};

template<typename T>
class aggregate_fields_type<3, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3] = obj;
        return f(a1,a2,a3);
    }
};

template<typename T>
class aggregate_fields_type<4, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4] = obj;
        return f(a1,a2,a3,a4);
    }
};

template<typename T>
class aggregate_fields_type<5, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5] = obj;
        return f(a1,a2,a3,a4,a5);
    }
};

template<typename T>
class aggregate_fields_type<6, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6] = obj;
        return f(a1,a2,a3,a4,a5,a6);
    }
};

template<typename T>
class aggregate_fields_type<7, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7);
    }
};

template<typename T>
class aggregate_fields_type<8, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8);
    }
};

template<typename T>
class aggregate_fields_type<9, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9);
    }
};

template<typename T>
class aggregate_fields_type<10, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
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
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10
              ] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10
              );
    }
};

template<typename T>
class aggregate_fields_type<11, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11);
    }
};

template<typename T>
class aggregate_fields_type<12, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12);
    }
};

template<typename T>
class aggregate_fields_type<13, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13);
    }
};

template<typename T>
class aggregate_fields_type<14, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14);
    }
};

template<typename T>
class aggregate_fields_type<15, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15);
    }
};

template<typename T>
class aggregate_fields_type<16, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16);
    }
};

template<typename T>
class aggregate_fields_type<17, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17);
    }
};

template<typename T>
class aggregate_fields_type<18, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18);
    }
};

template<typename T>
class aggregate_fields_type<19, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19);
    }
};

template<typename T>
class aggregate_fields_type<20, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20
              ] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20
              ] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20
              );
    }
};

template<typename T>
class aggregate_fields_type<21, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21);
    }
};

template<typename T>
class aggregate_fields_type<22, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22);
    }
};

template<typename T>
class aggregate_fields_type<23, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23);
    }
};

template<typename T>
class aggregate_fields_type<24, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24);
    }
};

template<typename T>
class aggregate_fields_type<25, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25);
    }
};

template<typename T>
class aggregate_fields_type<26, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26);
    }
};

template<typename T>
class aggregate_fields_type<27, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27);
    }
};

template<typename T>
class aggregate_fields_type<28, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28);
    }
};

template<typename T>
class aggregate_fields_type<29, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29);
    }
};

template<typename T>
class aggregate_fields_type<30, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30
              ] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30
              ] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30
              );
    }
};

template<typename T>
class aggregate_fields_type<31, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31);
    }
};

template<typename T>
class aggregate_fields_type<32, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32);
    }
};

template<typename T>
class aggregate_fields_type<33, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33);
    }
};

template<typename T>
class aggregate_fields_type<34, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34);
    }
};

template<typename T>
class aggregate_fields_type<35, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35);
    }
};

template<typename T>
class aggregate_fields_type<36, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36);
    }
};

template<typename T>
class aggregate_fields_type<37, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37);
    }
};

template<typename T>
class aggregate_fields_type<38, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38);
    }
};

template<typename T>
class aggregate_fields_type<39, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39);
    }
};

template<typename T>
class aggregate_fields_type<40, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40
              ] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40
              ] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40
              );
    }
};

template<typename T>
class aggregate_fields_type<41, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41);
    }
};

template<typename T>
class aggregate_fields_type<42, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42);
    }
};

template<typename T>
class aggregate_fields_type<43, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43);
    }
};

template<typename T>
class aggregate_fields_type<44, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44);
    }
};

template<typename T>
class aggregate_fields_type<45, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45);
    }
};

template<typename T>
class aggregate_fields_type<46, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46);
    }
};

template<typename T>
class aggregate_fields_type<47, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47);
    }
};

template<typename T>
class aggregate_fields_type<48, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48);
    }
};

template<typename T>
class aggregate_fields_type<49, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49);
    }
};

template<typename T>
class aggregate_fields_type<50, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50
              ] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50
              ] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50
              );
    }
};

template<typename T>
class aggregate_fields_type<51, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51);
    }
};

template<typename T>
class aggregate_fields_type<52, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52);
    }
};

template<typename T>
class aggregate_fields_type<53, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53);
    }
};

template<typename T>
class aggregate_fields_type<54, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54);
    }
};

template<typename T>
class aggregate_fields_type<55, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55);
    }
};

template<typename T>
class aggregate_fields_type<56, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56);
    }
};

template<typename T>
class aggregate_fields_type<57, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57);
    }
};

template<typename T>
class aggregate_fields_type<58, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58);
    }
};

template<typename T>
class aggregate_fields_type<59, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59);
    }
};

template<typename T>
class aggregate_fields_type<60, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60
              ] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60
              ] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60
              );
    }
};

template<typename T>
class aggregate_fields_type<61, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61);
    }
};

template<typename T>
class aggregate_fields_type<62, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62);
    }
};

template<typename T>
class aggregate_fields_type<63, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63);
    }
};

template<typename T>
class aggregate_fields_type<64, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64);
    }
};

template<typename T>
class aggregate_fields_type<65, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65);
    }
};

template<typename T>
class aggregate_fields_type<66, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66);
    }
};

template<typename T>
class aggregate_fields_type<67, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67);
    }
};

template<typename T>
class aggregate_fields_type<68, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68);
    }
};

template<typename T>
class aggregate_fields_type<69, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69);
    }
};

template<typename T>
class aggregate_fields_type<70, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70
              ] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70
              ] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70
              );
    }
};

template<typename T>
class aggregate_fields_type<71, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71);
    }
};

template<typename T>
class aggregate_fields_type<72, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72);
    }
};

template<typename T>
class aggregate_fields_type<73, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73);
    }
};

template<typename T>
class aggregate_fields_type<74, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74);
    }
};

template<typename T>
class aggregate_fields_type<75, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75);
    }
};

template<typename T>
class aggregate_fields_type<76, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76);
    }
};

template<typename T>
class aggregate_fields_type<77, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77);
    }
};

template<typename T>
class aggregate_fields_type<78, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78);
    }
};

template<typename T>
class aggregate_fields_type<79, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79);
    }
};

template<typename T>
class aggregate_fields_type<80, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80
              ] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80
              ] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80
              );
    }
};

template<typename T>
class aggregate_fields_type<81, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81);
    }
};

template<typename T>
class aggregate_fields_type<82, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82);
    }
};

template<typename T>
class aggregate_fields_type<83, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83);
    }
};

template<typename T>
class aggregate_fields_type<84, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84);
    }
};

template<typename T>
class aggregate_fields_type<85, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85);
    }
};

template<typename T>
class aggregate_fields_type<86, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86);
    }
};

template<typename T>
class aggregate_fields_type<87, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87);
    }
};

template<typename T>
class aggregate_fields_type<88, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88);
    }
};

template<typename T>
class aggregate_fields_type<89, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89);
    }
};

template<typename T>
class aggregate_fields_type<90, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90
              ] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89),decltype(a90)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90
              ] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90
              );
    }
};

template<typename T>
class aggregate_fields_type<91, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89),decltype(a90),
              decltype(a91)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91);
    }
};

template<typename T>
class aggregate_fields_type<92, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89),decltype(a90),
              decltype(a91),decltype(a92)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92);
    }
};

template<typename T>
class aggregate_fields_type<93, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89),decltype(a90),
              decltype(a91),decltype(a92),decltype(a93)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93);
    }
};

template<typename T>
class aggregate_fields_type<94, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89),decltype(a90),
              decltype(a91),decltype(a92),decltype(a93),decltype(a94)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94);
    }
};

template<typename T>
class aggregate_fields_type<95, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89),decltype(a90),
              decltype(a91),decltype(a92),decltype(a93),decltype(a94),decltype(a95)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95);
    }
};

template<typename T>
class aggregate_fields_type<96, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89),decltype(a90),
              decltype(a91),decltype(a92),decltype(a93),decltype(a94),decltype(a95),
              decltype(a96)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96);
    }
};

template<typename T>
class aggregate_fields_type<97, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89),decltype(a90),
              decltype(a91),decltype(a92),decltype(a93),decltype(a94),decltype(a95),
              decltype(a96),decltype(a97)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97);
    }
};

template<typename T>
class aggregate_fields_type<98, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97,a98] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89),decltype(a90),
              decltype(a91),decltype(a92),decltype(a93),decltype(a94),decltype(a95),
              decltype(a96),decltype(a97),decltype(a98)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97,a98] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97,a98);
    }
};

template<typename T>
class aggregate_fields_type<99, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97,a98,a99] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89),decltype(a90),
              decltype(a91),decltype(a92),decltype(a93),decltype(a94),decltype(a95),
              decltype(a96),decltype(a97),decltype(a98),decltype(a99)>{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97,a98,a99] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97,a98,a99);
    }
};

template<typename T>
class aggregate_fields_type<100, T, std::enable_if_t<std::is_aggregate_v<T>>> { 
    constexpr static auto deduce_type() {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97,a98,a99,a100
              ] = T{};
        return type_list<decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),
              decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10),
              decltype(a11),decltype(a12),decltype(a13),decltype(a14),decltype(a15),
              decltype(a16),decltype(a17),decltype(a18),decltype(a19),decltype(a20),
              decltype(a21),decltype(a22),decltype(a23),decltype(a24),decltype(a25),
              decltype(a26),decltype(a27),decltype(a28),decltype(a29),decltype(a30),
              decltype(a31),decltype(a32),decltype(a33),decltype(a34),decltype(a35),
              decltype(a36),decltype(a37),decltype(a38),decltype(a39),decltype(a40),
              decltype(a41),decltype(a42),decltype(a43),decltype(a44),decltype(a45),
              decltype(a46),decltype(a47),decltype(a48),decltype(a49),decltype(a50),
              decltype(a51),decltype(a52),decltype(a53),decltype(a54),decltype(a55),
              decltype(a56),decltype(a57),decltype(a58),decltype(a59),decltype(a60),
              decltype(a61),decltype(a62),decltype(a63),decltype(a64),decltype(a65),
              decltype(a66),decltype(a67),decltype(a68),decltype(a69),decltype(a70),
              decltype(a71),decltype(a72),decltype(a73),decltype(a74),decltype(a75),
              decltype(a76),decltype(a77),decltype(a78),decltype(a79),decltype(a80),
              decltype(a81),decltype(a82),decltype(a83),decltype(a84),decltype(a85),
              decltype(a86),decltype(a87),decltype(a88),decltype(a89),decltype(a90),
              decltype(a91),decltype(a92),decltype(a93),decltype(a94),decltype(a95),
              decltype(a96),decltype(a97),decltype(a98),decltype(a99),decltype(a100)
              >{};
    }    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(T& obj, F& f) {
        auto [a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97,a98,a99,a100
              ] = obj;
        return f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,
              a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
              a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,
              a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,
              a41,a42,a43,a44,a45,a46,a47,a48,a49,a50,
              a51,a52,a53,a54,a55,a56,a57,a58,a59,a60,
              a61,a62,a63,a64,a65,a66,a67,a68,a69,a70,
              a71,a72,a73,a74,a75,a76,a77,a78,a79,a80,
              a81,a82,a83,a84,a85,a86,a87,a88,a89,a90,
              a91,a92,a93,a94,a95,a96,a97,a98,a99,a100
              );
    }
};

}

NANO_CAF_NS_END

#endif
