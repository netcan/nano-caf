cmake_minimum_required(VERSION 3.16)
project(nano_caf)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/third-party"
)

add_executable(nano_caf-test
        include/nano-caf/nano-caf-ns.h
        include/nano-caf/core/actor_system.h
        third-party/catch.hpp tests/ut/test_lifo_inbox.cpp include/nano-caf/util/disable_copy.h include/nano-caf/core/lifo_inbox.h include/nano-caf/core/message_element.h tests/ut/catch.cpp src/core/lifo_inbox.cpp include/nano-caf/core/actor_inbox.h src/core/actor_inbox.cpp include/nano-caf/core/actor_storage.h include/nano-caf/core/thread_safe_list.h include/nano-caf/core/spin_lock.h)