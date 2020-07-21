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
        third-party/catch.hpp tests/ut/TestLIFO.cpp include/nano-caf/util/disable_copy.h include/nano-caf/core/lifo_queue.h include/nano-caf/core/message_element.h tests/ut/catch.cpp)