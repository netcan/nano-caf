//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_MESSAGE_ID_H
#define NANO_CAF_MESSAGE_ID_H

#include <nano-caf/nano-caf-ns.h>
#include <nano-caf/core/msg/message_trait.h>
#include <cstdint>

NANO_CAF_NS_BEGIN

struct message_id {
   enum category : uint64_t {
      future = uint64_t(1) << 61,
      normal = uint64_t(1) << 62,
      urgent = uint64_t(1) << 63,
   };

   constexpr message_id(uint64_t id, bool is_urgent = false)
      : message_id(id, is_urgent ? urgent : normal)
   {}

   constexpr message_id(uint64_t id, category category)
      : id{(id & mask) | ((uint64_t)category)}
   {}

   auto is_category(category category) const -> bool {
      return id & ((uint64_t)category);
   }

   auto operator==(const message_id& rhs) const {
      return id == rhs.id;
   }
   auto operator!=(const message_id& rhs) const {
      return !operator==(rhs);
   }

   operator uint64_t() const {
      return id;
   }
private:
   enum : uint64_t {
      mask = (uint64_t)category::normal - 1
   };
private:
   uint64_t id;
};

constexpr message_id EXIT_MSG{0x0000'FFFF'FFFF'FFFF, message_id::category::urgent };

NANO_CAF_NS_END

#endif //NANO_CAF_MESSAGE_ID_H
