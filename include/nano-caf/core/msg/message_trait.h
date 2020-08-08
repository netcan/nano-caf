//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_MESSAGE_TRAIT_H
#define NANO_CAF_MESSAGE_TRAIT_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/atom.h>
#include <nano-caf/util/macro_reflex.h>

NANO_CAF_NS_BEGIN

///////////////////////////////////////////////////////////////////////////////////////////////
#define __CAF_def_message(name, ...) \
struct name; \
struct name##_atom : NANO_CAF_NS::atom_signature { \
    using msg_type = name; \
}; \
struct name { \
   __CUB_fields_only(__VA_ARGS__) \
}

///////////////////////////////////////////////////////////////////////////////////////////////
#define CAF_def_message(name, ...) __CAF_def_message(name, ##__VA_ARGS__)

NANO_CAF_NS_END

#endif //NANO_CAF_MESSAGE_TRAIT_H
