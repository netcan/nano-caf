//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_CANCELLABLE_H
#define NANO_CAF_CANCELLABLE_H

#include <nano-caf/util/status_t.h>

NANO_CAF_NS_BEGIN

struct cancellable {
   virtual auto cancel(status_t cause) noexcept -> void = 0;
   virtual auto start_timer(uint64_t duration, std::weak_ptr<cancellable>) noexcept -> status_t = 0;
   virtual auto timeout() noexcept -> void = 0;
   virtual ~cancellable() = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_CANCELLABLE_H
