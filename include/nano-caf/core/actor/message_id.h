//
// Created by Darwin Yuan on 2020/7/22.
//

#ifndef NANO_CAF_MESSAGE_ID_H
#define NANO_CAF_MESSAGE_ID_H

#include <nano-caf/nano-caf-ns.h>
#include <cstdint>

NANO_CAF_NS_BEGIN

struct message_id {
   enum class category : uint32_t {
      normal = uint32_t(1) << 30,
      urgent = uint32_t(1) << 31,
   };

   message_id(uint32_t id, category category)
      : id{(id & mask) | ((uint32_t)category)}
   {}

   auto is_category(category category) const -> bool {
      return id & ((uint32_t)category);
   }

   auto operator==(const message_id& rhs) const {
      return id == rhs.id;
   }
   auto operator!=(const message_id& rhs) const {
      return !operator==(rhs);
   }

private:
   enum : uint32_t {
      mask = (uint32_t)category::normal - 1
   };
private:
   uint32_t id;
};

NANO_CAF_NS_END

#endif //NANO_CAF_MESSAGE_ID_H
