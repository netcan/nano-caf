//
// Created by Darwin Yuan on 2020/7/25.
//

#ifndef NANO_CAF_INTRUSIVE_ACTOR_PTR_H
#define NANO_CAF_INTRUSIVE_ACTOR_PTR_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/util/intrusive_ptr.h>

NANO_CAF_NS_BEGIN

struct actor_control_block;

using intrusive_actor_ptr = intrusive_ptr<actor_control_block>;

auto intrusive_ptr_add_weak_ref(actor_control_block* x) noexcept -> void;
auto intrusive_ptr_add_ref(actor_control_block* x) noexcept -> void;
auto intrusive_ptr_release_weak(actor_control_block* x) noexcept -> void;
auto intrusive_ptr_release(actor_control_block* x) noexcept -> void;
auto intrusive_ptr_upgrade_weak(actor_control_block* x) noexcept -> intrusive_actor_ptr;

NANO_CAF_NS_END

#endif //NANO_CAF_INTRUSIVE_ACTOR_PTR_H
