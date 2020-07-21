cmake_minimum_required(VERSION 3.16)
project(nano_caf)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/third-party"
)

add_library(nano_caf
        include/nano-caf/nano-caf-ns.h
        include/nano-caf/core/actor_system.h
        third-party/catch.hpp)