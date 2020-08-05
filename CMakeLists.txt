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
        include/nano-caf/util/disable_copy.h
        include/nano-caf/core/actor/lifo_inbox.h
        include/nano-caf/core/msg/message.h
        src/core/actor/lifo_inbox.cpp
        include/nano-caf/core/actor/actor_inbox.h
        src/core/actor/actor_inbox.cpp
        include/nano-caf/core/actor/actor_storage.h
        include/nano-caf/core/thread_safe_list.h
        include/nano-caf/core/spin_lock.h
        include/nano-caf/core/msg/message_id.h
        include/nano-caf/core/actor/task_list.h
        include/nano-caf/core/actor/drr_cached_queue.h
        src/core/actor/task_list.cpp
        src/core/actor/ddr_cached_queue.cpp
        include/nano-caf/core/new_round_result.h
        include/nano-caf/core/resumable.h
        include/nano-caf/core/actor/sched_actor.h
        src/core/actor/sched_actor.cpp
        include/nano-caf/util/intrusive_ptr.h
        include/nano-caf/core/actor/actor_control_block.h
        src/core/actor/actor_control_block.cpp
        include/nano-caf/core/cache_line_size.h
        include/nano-caf/core/worker.h
        src/core/worker.cpp tests/ut/test_worker.cpp
        include/nano-caf/core/actor/make_actor.h
        include/nano-caf/core/coordinator.h
        src/core/coordinator.cpp
        src/core/actor_system.cpp
        include/nano-caf/core/actor/actor_handle.h
        src/core/actor/actor_handle.cpp
        include/nano-caf/core/actor/exit_reason.h
        include/nano-caf/util/list_element.h
        include/nano-caf/core/actor/enq_result.h
        include/nano-caf/core/actor/actor.h
        include/nano-caf/core/actor/intrusive_actor_ptr.h
        include/nano-caf/core/actor_context.h
        src/core/actor/actor_context.cpp
        include/nano-caf/core/actor/wait_result.h
        include/nano-caf/core/await/async_object.h
        include/nano-caf/core/await/future_callback.h
        include/nano-caf/util/callable_trait.h
        include/nano-caf/core/msg/message_trait.h
        include/nano-caf/util/type_list.h
        include/nano-caf/core/msg/predefined-msgs.h
        include/nano-caf/core/actor/behavior.h
        include/nano-caf/util/macro_reflex.h
        include/nano-caf/util/macro_pp_size.h
        include/nano-caf/core/actor/behavior_based_actor.h
        include/nano-caf/util/macro_basic.h
        include/nano-caf/util/aggregate_fields_type.h
        include/nano-caf/util/aggregate_reflex.h
        include/nano-caf/core/msg/make_message.h
        include/nano-caf/core/actor/drr_queue.h
        src/core/actor/drr_queue.cpp
        include/nano-caf/util/either.h
        include/nano-caf/util/unit.h include/nano-caf/util/likely.h include/nano-caf/core/double_end_list.h src/core/double_end_list.cpp src/core/thread_safe_list.cpp include/nano-caf/core/lock_free_list.h include/nano-caf/core/double_end_list_elem.h src/core/lock_free_list.cpp include/nano-caf/core/actor/task_stack.h include/nano-caf/core/actor/task_result.h src/core/actor/task_stack.cpp include/nano-caf/util/macro_meta_data.h include/nano-caf/util/macro_struct.h)

add_executable(nano_caf-test
        third-party/catch.hpp
        tests/ut/test_lifo_inbox.cpp
        tests/ut/catch.cpp
        tests/ut/test_task_list.cpp
        tests/ut/test_drr_cached_queue.cpp
        tests/ut/test_actor_inbox.cpp
        tests/ut/test_sched_actor.cpp
        tests/ut/test_actor_system.cpp
        tests/ut/test_msgs.h
        tests/ut/test_behavior.cpp tests/ut/test_double_end_list.cpp tests/ut/test_lock_free_list.cpp tests/ut/test_ro_meta.cpp)

add_executable(test_actor_system
        tests/ft/test_actor_system.cpp)

add_executable(test_async tests/ft/test_async.cpp
        third-party/nanobench.h
        tests/ut/nanobench.cpp)

add_executable(test_ping_pong
        tests/ft/test_ping_pong.cpp)

add_executable(test_job_queue
        tests/ft/test_job_queue.cpp
        third-party/nanobench.h
        tests/ut/nanobench.cpp)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(UNIX)
    target_link_libraries(nano_caf-test nano_caf pthread)
    target_link_libraries(test_actor_system nano_caf pthread)
    target_link_libraries(test_ping_pong nano_caf pthread)
    target_link_libraries(test_async nano_caf pthread)
    target_link_libraries(test_job_queue nano_caf pthread)
else()
    target_link_libraries(nano_caf-test nano_caf)
    target_link_libraries(test_actor_system nano_caf)
    target_link_libraries(test_ping_pong nano_caf)
    target_link_libraries(test_async nano_caf)
    target_link_libraries(test_job_queue nano_caf)
endif()
