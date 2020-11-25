//
// Created by Darwin Yuan on 2020/10/2.
//

#ifndef NANO_CAF_TIME_GUARD_OBJECT_H
#define NANO_CAF_TIME_GUARD_OBJECT_H

#include <nano-caf/core/await/detail/future_object.h>

NANO_CAF_NS_BEGIN namespace detail {

struct time_guard_object : future_object<void>, future_observer {
   using super = future_object<void>;
   using super::super;

private:
   using subject_type = std::shared_ptr<future_object<void>>;
   std::optional<timer_id_t> timer_id_;
};

} NANO_CAF_NS_END

#endif //NANO_CAF_TIME_GUARD_OBJECT_H
