//
// Created by Darwin Yuan on 2020/7/23.
//

#ifndef NANO_CAF_NEW_ROUND_RESULT_H
#define NANO_CAF_NEW_ROUND_RESULT_H

#include <nano-caf/nano-caf-ns.h>
#include <cstddef>

NANO_CAF_NS_BEGIN

struct new_round_result {
   size_t consumed_items;
   bool stop_all;

   auto tie() const {
      return std::tie(consumed_items, stop_all);
   }
};

inline bool operator==(const new_round_result& lhs, const new_round_result& rhs) noexcept {
   return lhs.tie() == rhs.tie();
}

inline bool operator!=(const new_round_result& lhs, const new_round_result& rhs) noexcept {
   return lhs.tie() != rhs.tie();
}

NANO_CAF_NS_END

#endif //NANO_CAF_NEW_ROUND_RESULT_H
