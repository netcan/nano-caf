//
// Created by Darwin Yuan on 2020/8/2.
//

#ifndef NANO_CAF_LIKELY_H
#define NANO_CAF_LIKELY_H

#define __likely(x)    __builtin_expect((x),1)
#define __unlikely(x)  __builtin_expect((x),0)

#endif //NANO_CAF_LIKELY_H
