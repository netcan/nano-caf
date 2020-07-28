//
// Created by Darwin Yuan on 2020/7/28.
//

CAF_begin_message_def(my_message)
   CAF_msg_field(amount, int)
   CAF_msg_field(currency, double)
CAF_end_message_def()


CAF_begin_message_def(test_message)
   CAF_msg_field(value, int)
CAF_end_message_def()

CAF_begin_message_def(shared_buf_msg)
   CAF_msg_field(obj, std::shared_ptr<big_msg>)
CAF_end_message_def()
