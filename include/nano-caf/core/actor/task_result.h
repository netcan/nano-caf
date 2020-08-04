//
// Created by Darwin Yuan on 2020/8/4.
//

#ifndef NANO_CAF_TASK_RESULT_H
#define NANO_CAF_TASK_RESULT_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

enum class task_result {
   resume,
   skip,
   done
};

NANO_CAF_NS_END

#endif //NANO_CAF_TASK_RESULT_H
