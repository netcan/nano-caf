//
// Created by Darwin Yuan on 2020/7/28.
//

#define __CAF_def_message(name, id) \
struct name; \
struct name##_atom {}; \
template<> struct from_msg_type_to_id<name>          { constexpr static msg_id_t msg_id = id; }; \
template<> struct from_atom_to_msg_type<name##_atom> { using type = name; }; \
struct name {

#include <nano-caf/core/msg/message_interp_end.h>
#define CAF_begin_message_def(name) __CAF_def_message(name, __COUNTER__)
#define CAF_msg_field(name, type) type name;
#define CAF_end_message_def() };

