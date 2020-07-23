//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_ACTOR_STORAGE_H
#define NANO_CAF_ACTOR_STORAGE_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/message_element.h>
#include <nano-caf/core/lifo_inbox.h>
#include <nano-caf/core/actor_control_block.h>

NANO_CAF_NS_BEGIN

template<typename T>
struct actor_storage  {

private:
   static_assert(sizeof(actor_control_block) <= CACHE_LINE_SIZE);
   actor_control_block controlBlock;
   char padding[CACHE_LINE_SIZE - sizeof(controlBlock)];
   union { T value; };
};

NANO_CAF_NS_END

#endif //NANO_CAF_ACTOR_STORAGE_H
