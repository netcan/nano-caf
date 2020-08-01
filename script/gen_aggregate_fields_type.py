
import sys

head = '''
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

'''

tail = '''
}

NANO_CAF_NS_END

#endif
'''

name = '''
template<typename T>
class aggregate_fields_type<{0}, T, std::enable_if_t<std::is_aggregate_v<T>>> {{ 
    constexpr static auto deduce_type() {{
        auto [{1}] = T{{}};
        return type_list<{2}>{{}};
    }}    
public:
    using type = decltype(deduce_type());
    
    template <typename F>
    static auto call(const T& obj, F&& f) {{
        auto [{3}] = obj;
        return f({4});
    }}
}};
'''

def gen_one(n):
    bindings = ""
    decltypes = ""
    m = 0
    for i in range(n):
        bindings = bindings + "a{}".format(i+1)
        decltypes = decltypes + "decltype(a{})".format(i+1)
        if i < n-1:
            bindings = bindings + ","
            decltypes = decltypes + ","
        m = m+1
        if m % 10 == 0:
            bindings = bindings + "\n              "
        if m % 5 == 0:
            decltypes = decltypes + "\n              "

    return name.format(n, bindings, decltypes, bindings, bindings)

def gen_all(n):
    all = ""
    for i in range(n):
        all = all + gen_one(i+1)

    return all

def main():
    # print command line arguments
    if len(sys.argv) != 3:
        print("specify the num and file")
        exit(-1)

    n = int(sys.argv[1])
    lines = head + gen_all(n) + tail

    file = open(sys.argv[2], "w")
    file.writelines(lines)
    file.close()

if __name__ == "__main__":
    main()