//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_AWAITER_H
#define NANO_CAF_AWAITER_H

#include <nano-caf/util/status_t.h>
#include <memory>

NANO_CAF_NS_BEGIN

struct awaiter {
   virtual auto cancel(status_t cause) noexcept -> void = 0;
   virtual auto start_timer(uint64_t duration, std::weak_ptr<awaiter>) noexcept -> status_t = 0;
   virtual auto timeout() noexcept -> void = 0;
   virtual ~awaiter() = default;
};

NANO_CAF_NS_END

#endif //NANO_CAF_AWAITER_H
