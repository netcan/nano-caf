//
// Created by Darwin Yuan on 2020/8/2.
//

#ifndef NANO_CAF_UNIT_H
#define NANO_CAF_UNIT_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

struct unit_t {
   constexpr unit_t() = default;
   auto operator==(const unit_t&) const -> bool { return true; }
   auto operator!=(const unit_t&) const -> bool { return false; }
};

inline constexpr unit_t unit{};

NANO_CAF_NS_END

#endif //NANO_CAF_UNIT_H
