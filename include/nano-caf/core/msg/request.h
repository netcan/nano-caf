//
// Created by Darwin Yuan on 2020/8/8.
//

#ifndef NANO_CAF_REQUEST_H
#define NANO_CAF_REQUEST_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/atom.h>

NANO_CAF_NS_BEGIN

template<typename ... Ts>
struct typed_actor {

};

struct atom_1 : atom_signature {};
struct atom_2 : atom_signature {};

#define METHOD(method, signature) \
struct method ##_atom : atom_signature { \
   using type = auto signature; \
}


struct actor_interface {
   METHOD(a, (int) -> int);
   METHOD(b, (int) -> void);
};

NANO_CAF_NS_END

#endif //NANO_CAF_REQUEST_H
