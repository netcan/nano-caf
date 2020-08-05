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

#define __CUB_keep__(...) __VA_ARGS__
#define __CUB_eat__(...)
#define __CUB_split__(...) __VA_ARGS__ ,

#define __CUB_1st__(a, ...) a
#define __CUB_1st(...) __CUB_1st__(__VA_ARGS__)

#endif //NANO_CAF_MACRO_BASIC_H
