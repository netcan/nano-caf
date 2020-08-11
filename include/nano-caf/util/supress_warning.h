//
// Created by Darwin Yuan on 2020/8/11.
//

#ifndef NANO_CAF_SUPRESS_WARNING_H
#define NANO_CAF_SUPRESS_WARNING_H

#if defined(__CLANG__) || defined(__GNUC__)
#define DISABLE_WARNING_PUSH _Pragma("GCC diagnostic push")
#define DISABLE_WARNING_POP _Pragma("GCC diagnostic pop")
#define DISABLE_WARNING_MISS_FIELD _Pragma(R"(GCC diagnostic ignored "-Wmissing-field-initializers")")
#else
#define DISABLE_WARNING_PUSH
#define DISABLE_WARNING_POP
#define DISABLE_WARNING_MISS_FIELD
#endif

#endif //NANO_CAF_SUPRESS_WARNING_H
