//
// Created by Darwin Yuan on 2020/7/23.
//

#ifndef NANO_CAF_NEW_ROUND_RESULT_H
#define NANO_CAF_NEW_ROUND_RESULT_H

#include <nano-caf/nano-caf-ns.h>
#include <cstddef>

NANO_CAF_NS_BEGIN

struct new_round_result {
   size_t consumed_items;
   bool stop_all;
};

NANO_CAF_NS_END

#endif //NANO_CAF_NEW_ROUND_RESULT_H
