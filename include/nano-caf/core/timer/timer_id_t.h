//
// Created by Darwin Yuan on 2020/9/17.
//

#ifndef NANO_CAF_TIMER_ID_T_H
#define NANO_CAF_TIMER_ID_T_H

#include <nano-caf/nano-caf-ns.h>
#include <cstdint>

NANO_CAF_NS_BEGIN

struct timer_id_t {
   explicit timer_id_t(uint64_t id) : id_{id} {}

   auto operator==(timer_id_t& rhs) const { return id_ == rhs.id_; }
   auto operator!=(timer_id_t& rhs) const { return id_ != rhs.id_; }
   auto operator<(timer_id_t& rhs) const  { return id_ < rhs.id_; }

private:
   uint64_t id_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_TIMER_ID_T_H
