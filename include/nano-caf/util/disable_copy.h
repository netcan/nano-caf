//
// Created by Darwin Yuan on 2020/7/21.
//

#ifndef NANO_CAF_DISABLE_COPY_H
#define NANO_CAF_DISABLE_COPY_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

struct disable_copy {
   disable_copy(const disable_copy&) = delete;
   disable_copy(disable_copy&&) = delete;
   disable_copy& operator=(const disable_copy&) = delete;
   disable_copy& operator=(disable_copy&&) = delete;
};

NANO_CAF_NS_END

#endif //NANO_CAF_DISABLE_COPY_H
