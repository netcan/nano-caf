//
// Created by Darwin Yuan on 2020/7/24.
//

#ifndef NANO_CAF_WORKER_H
#define NANO_CAF_WORKER_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/actor/message_element.h>
#include <cstddef>
#include <memory>

NANO_CAF_NS_BEGIN

struct worker {
   auto launch() -> void;
};

NANO_CAF_NS_END

#endif //NANO_CAF_WORKER_H
