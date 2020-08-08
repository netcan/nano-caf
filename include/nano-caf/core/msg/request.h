//
// Created by Darwin Yuan on 2020/8/8.
//

#ifndef NANO_CAF_REQUEST_H
#define NANO_CAF_REQUEST_H

template<typename ... Ts>
struct typed_actor {

};

using actor1 = typed_actor<auto (int) -> int, auto() -> void>;

#endif //NANO_CAF_REQUEST_H
