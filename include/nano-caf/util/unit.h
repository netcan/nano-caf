//
// Created by Darwin Yuan on 2020/8/2.
//

#ifndef NANO_CAF_UNIT_H
#define NANO_CAF_UNIT_H

#include <nano-caf/nano-caf-ns.h>

NANO_CAF_NS_BEGIN

struct unit_t {
   struct __secret_tag { inline __secret_tag() = default; };
   constexpr unit_t(__secret_tag, __secret_tag){}
   auto operator==(const unit_t&) const -> bool { return true; }
   auto operator!=(const unit_t&) const -> bool { return false; }
};

inline constexpr unit_t unit{unit_t::__secret_tag{}, unit_t::__secret_tag{}};

NANO_CAF_NS_END

#endif //NANO_CAF_UNIT_H
