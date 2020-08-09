//
// Created by Darwin Yuan on 2020/8/9.
//

#ifndef NANO_CAF_STATUS_T_H
#define NANO_CAF_STATUS_T_H

#include <nano-caf/nano-caf-ns.h>
#include <utility>

NANO_CAF_NS_BEGIN

enum status_t : std::uint_fast64_t {
   ok,
   failed,
   timeout
};

NANO_CAF_NS_END

#endif //NANO_CAF_STATUS_T_H
