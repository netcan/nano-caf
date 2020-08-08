////
//// Created by Darwin Yuan on 2020/7/22.
////
//
//#ifndef NANO_CAF_MESSAGE_ID_H
//#define NANO_CAF_MESSAGE_ID_H
//
//#include <nano-caf/nano-caf-ns.h>
//#include <nano-caf/core/msg/message_trait.h>
//#include <cstdint>
//
//NANO_CAF_NS_BEGIN
//
//class message_id {
//   enum : uint64_t {
//      future_mask = uint64_t(1) << 61,
//      normal_mask = uint64_t(1) << 62,
//      urgent_mask = uint64_t(1) << 63,
//   };
//
//   enum : uint64_t {
//      future = future_mask | normal_mask
//   };
//
//public:
//   enum category : uint64_t {
//      normal = normal_mask,
//      urgent = urgent_mask,
//   };
//
//   constexpr message_id(uint64_t id, category category)
//      : id{(id & mask) | category }
//   {}
//
//   auto is_category(category category) const -> bool {
//      return id & category;
//   }
//
//   auto test_flag(uint64_t flag) const -> bool {
//      return id & flag;
//   }
//
//   auto operator==(const message_id& rhs) const {
//      return id == rhs.id;
//   }
//
//   auto operator!=(const message_id& rhs) const {
//      return !operator==(rhs);
//   }
//
//   operator uint64_t() const {
//      return id;
//   }
//
//   auto get_id() const -> msg_id_t {
//      return id & mask;
//   }
//
//   friend struct message;
//
//   template <typename F, typename R>
//   friend struct async_object;
//
//private:
//   enum : uint64_t {
//      mask = 0x0000'0000'FFFF'FFFF
//   };
//
//private:
//   uint64_t id;
//};
//
//NANO_CAF_NS_END
//
//#endif //NANO_CAF_MESSAGE_ID_H
