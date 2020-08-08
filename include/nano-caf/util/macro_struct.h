//
// Created by Darwin Yuan on 2020/8/5.
//

#ifndef NANO_CAF_MACRO_STRUCT_H
#define NANO_CAF_MACRO_STRUCT_H

#include <nano-caf/util/macro_basic.h>

#define __CUB_var_full(x) __CUB_swap_ x
#define __CUB_var_name(x) __CUB_1st   x
#define __CUB_var_type(x) __CUB_rest  x

#define __CUB_all_fields__(macro, ...) \
__CUB_overload(__CUB_repeat_call_, __VA_ARGS__) (macro, 0, __VA_ARGS__)

#endif //NANO_CAF_MACRO_STRUCT_H
