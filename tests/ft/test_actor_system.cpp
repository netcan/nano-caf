//
// Created by godsme on 7/29/20.
//
#include <nano-caf/core/msg/message_element.h>
#include <nano-caf/core/actor/sched_actor.h>
#include <nano-caf/core/actor_system.h>
#include <nano-caf/core/actor/actor.h>
#include <iostream>
#include <nano-caf/core/actor/behavior_based_actor.h>
#include "../ut/test_msgs.h"

using namespace NANO_CAF_NS;

struct my_actor : actor {
    std::vector<size_t> values;
    auto handle_message(message_element& msg) noexcept -> task_result override {
        values.push_back(msg.body<test_message>()->value);
        return task_result::resume;
    }

    void clear() {
        values.clear();
    }
};

int main() {
    actor_system system;
    system.start(5);

    auto actor = system.spawn<my_actor>();

    actor.send<test_message>(1);
    //actor.release();

    system.power_off();
}