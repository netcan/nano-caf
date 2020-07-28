//
// Created by Darwin Yuan on 2020/7/28.
//

CAF_begin_message_def(my_message)
   CAF_msg_field(a, int)
   CAF_msg_field(b, double)
CAF_end_message_def()


CAF_begin_message_def(test_message)
   CAF_msg_field(a, int)
CAF_end_message_def()

CAF_begin_message_def(shared_buf_msg)
   CAF_msg_field(a, std::shared_ptr<big_msg>)
CAF_end_message_def()
