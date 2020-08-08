//
// Created by Darwin Yuan on 2020/8/8.
//

#ifndef NANO_CAF_ATOM_H
#define NANO_CAF_ATOM_H

#include <nano-caf/nano-caf-ns.h>
#include <type_traits>

NANO_CAF_NS_BEGIN

struct atom_signature {};

template<typename T>
constexpr bool is_msg_atom = std::is_base_of_v<atom_signature, T>;

NANO_CAF_NS_END

#endif //NANO_CAF_ATOM_H
