//
// Created by Darwin Yuan on 2020/7/31.
//

#ifndef NANO_CAF_MACRO_BASIC_H
#define NANO_CAF_MACRO_BASIC_H

#define __CUB_empty()
#define __CUB_concat(x, y) x ## y
#define __CUB_paste(x, y) __CUB_concat(x, y)

#define __CUB_stringify_(x) #x
#define __CUB_stringify(x) __CUB_stringify_(x)

#endif //NANO_CAF_MACRO_BASIC_H
