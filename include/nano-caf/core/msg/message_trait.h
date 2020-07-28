//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_MESSAGE_TRAIT_H
#define NANO_CAF_MESSAGE_TRAIT_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/type_list.h>
#include <cstdint>

NANO_CAF_NS_BEGIN

using msg_id_t = uint64_t;

template<typename> struct from_msg_type_to_id;
template<typename> struct from_atom_to_msg_type;
template<typename> struct from_msg_type_to_field;

struct __atom_signature {};

NANO_CAF_NS_END

#endif //NANO_CAF_MESSAGE_TRAIT_H
