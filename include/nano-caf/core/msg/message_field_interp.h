//
// Created by Darwin Yuan on 2020/7/28.
//

#include <nano-caf/core/msg/message_interp_end.h>

#define CAF_begin_message_def(name) \
template<> struct from_msg_type_to_field<name> { using type = type_list<void
#define CAF_msg_field(name, type) , type
#define CAF_end_message_def() >; };
