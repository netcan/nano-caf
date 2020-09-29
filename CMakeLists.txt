cmake_minimum_required(VERSION 3.16)
project(nano_caf)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnon-virtual-dtor \
#      -Wcast-align -Wunused -Woverloaded-virtual -Wconversion \
#      -Wsign-conversion -Wdouble-promotion -Wformat=2 \
#      -Wno-invalid-offsetof -fno-rtti -DDEBUG=1 -DSPDLOG_NO_EXCEPTIONS \
#      -Wno-builtin-macro-redefined -D'__FILE__=\"$(subst $(realpath ${CMAKE_SOURCE_DIR})/,,$(abspath $<))\"'")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSPDLOG_NO_EXCEPTIONS \
    -DDEBUG=1")

if(CMAKE_CXX_STANDARD EQUAL 20)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines -fno-exceptions")
endif()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-builtin-macro-redefined -D'__FILE__=\"$(subst $(realpath ${CMAKE_SOURCE_DIR})/,,$(abspath $<))\"'")


#if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}
#        -Wduplicated-cond
#        -Wduplicated-branches
#        -Wlogical-op
#        -Wuseless-cast")
#elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
#    -Wold-style-cast \
#    -fsanitize=address \
#    -fno-omit-frame-pointer \
#    -fsanitize=alignment \
#    -fsanitize=function \
#    -fsanitize=return \
#    -fsanitize=nullability \
#    -fsanitize=unreachable \
#    -fsanitize=null")
##endif()

include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/third-party"
        "${CMAKE_CURRENT_SOURCE_DIR}/../maco/include"
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
        include/nano-caf/core/thread_pool/thread_safe_list.h
        include/nano-caf/util/spin_lock.h
        include/nano-caf/core/actor/task_list.h
        include/nano-caf/core/actor/drr_cached_queue.h
        src/core/actor/task_list.cpp
        src/core/actor/ddr_cached_queue.cpp
        include/nano-caf/core/thread_pool/new_round_result.h
        include/nano-caf/core/thread_pool/resumable.h
        include/nano-caf/core/actor/sched_actor.h
        src/core/actor/sched_actor.cpp
        include/nano-caf/util/intrusive_ptr.h
        include/nano-caf/core/actor/actor_control_block.h
        src/core/actor/actor_control_block.cpp
        include/nano-caf/core/cache_line_size.h
        include/nano-caf/core/thread_pool/worker.h
        src/core/thread_pool/worker.cpp tests/ut/test_worker.cpp
        include/nano-caf/core/actor/make_actor.h
        include/nano-caf/core/thread_pool/coordinator.h
        src/core/thread_pool/coordinator.cpp
        src/core/actor_system.cpp
        include/nano-caf/core/actor/actor_handle.h
        include/nano-caf/core/actor/exit_reason.h
        include/nano-caf/util/list_element.h
        include/nano-caf/core/actor/enq_result.h
        include/nano-caf/core/actor/actor.h
        include/nano-caf/core/actor/intrusive_actor_ptr.h
        include/nano-caf/core/actor_context.h
        src/core/actor/system_actor_context.cpp
        include/nano-caf/core/await/async_object.h
        include/nano-caf/util/callable_trait.h
        include/nano-caf/core/msg/message_trait.h
        include/nano-caf/util/type_list.h
        include/nano-caf/core/msg/predefined-msgs.h
        include/nano-caf/core/actor/behavior.h
        include/nano-caf/util/macro_reflex.h
        include/nano-caf/core/actor/behavior_based_actor.h
        include/nano-caf/util/aggregate_fields_type.h
        include/nano-caf/util/aggregate_reflex.h
        include/nano-caf/core/msg/make_message.h
        include/nano-caf/core/actor/drr_queue.h
        src/core/actor/drr_queue.cpp
        include/nano-caf/util/either.h
        include/nano-caf/util/unit.h
        include/nano-caf/util/likely.h
        include/nano-caf/core/thread_pool/double_end_list.h
        src/core/thread_pool/double_end_list.cpp
        src/core/thread_pool/thread_safe_list.cpp
        include/nano-caf/core/thread_pool/lock_free_list.h
        include/nano-caf/core/thread_pool/double_end_list_elem.h
        src/core/thread_pool/lock_free_list.cpp
        include/nano-caf/core/actor/task_stack.h
        include/nano-caf/core/actor/task_result.h
        src/core/actor/task_stack.cpp
        include/nano-caf/util/maybe.h
        include/nano-caf/core/msg/request.h
        include/nano-caf/util/type_id_t.h
        include/nano-caf/core/msg/atom.h
        include/nano-caf/core/actor/typed_actor_handle.h
        include/nano-caf/util/status_t.h
        include/nano-caf/util/result_trait.h
        include/nano-caf/core/actor/requester.h
        include/nano-caf/util/suppress_warning.h
        include/nano-caf/util/cpp_attribute.h
        include/nano-caf/util/ptr_trait.h
        include/nano-caf/util/result_t.h
        include/nano-caf/core/system_actor_context.h
        include/nano-caf/core/timer/actor_timer.h
        src/core/timer/actor_timer.cpp
        include/nano-caf/util/cv_notifier.h
        include/nano-caf/core/timer/timer_set.h src/core/timer/timer_set.cpp
        include/nano-caf/core/actor/shutdown_notifier.h
        include/nano-caf/core/actor_registry.h src/core/actor_registry.cpp
        src/core/actor/intrusive_actor_ptr.cpp
        include/nano-caf/core/timer/timer_id_t.h
        include/nano-caf/core/timer/duration.h
        include/nano-caf/util/random_generator.h
        include/nano-caf/core/await/promise.h
        include/nano-caf/core/await/detail/future_object.h
        include/nano-caf/core/await/future.h
        include/nano-caf/core/await/abstract_promise.h
        include/nano-caf/core/await/promise_done_notifier.h
        include/nano-caf/core/await/detail/future_callback_base.h
        include/nano-caf/core/await/future_object_base.h
        include/nano-caf/core/await/future_repository.h include/nano-caf/core/await/detail/when_all_object.h include/nano-caf/core/await/detail/future_callback_object.h include/nano-caf/core/actor/on_actor_context.h include/nano-caf/core/actor/actor_timer_context.h include/nano-caf/core/await/detail/future_observer.h include/nano-caf/core/await/abstract_future.h include/nano-caf/core/await/failure_handler.h include/nano-caf/core/await/detail/tuple_trait.h include/nano-caf/core/await/detail/future_proxy_object.h include/nano-caf/core/await/detail/future_trait.h include/nano-caf/core/await/when_all.h)

if(CMAKE_CXX_STANDARD EQUAL 20)
    target_sources(nano_caf PRIVATE
            include/nano-caf/util/caf_log.h include/nano-caf/core/coroutine/co_actor_context.h
            include/nano-caf/core/coroutine/timer_task.h src/core/coroutine/timer_task.cpp
            include/nano-caf/core/coroutine/coro_registry.h
            include/nano-caf/core/coroutine/co_request.h
            include/nano-caf/core/actor/request_reply.h
            include/nano-caf/core/coroutine/awaitable_trait.h
            include/nano-caf/core/coroutine/co_timer.h
            include/nano-caf/core/coroutine/co_actor.h
            include/nano-caf/core/coroutine/actor_promise.h
            include/nano-caf/core/coroutine/cancellable_timer_awaiter.h
            include/nano-caf/core/coroutine/real_cancellable_timer_awaiter.h
            include/nano-caf/core/coroutine/co_actor_final_awaiter.h
            include/nano-caf/core/coroutine/co_task.h)
endif()

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
        tests/ut/test_behavior.cpp
        tests/ut/test_double_end_list.cpp
        tests/ut/test_lock_free_list.cpp
        tests/ut/test_ro_meta.cpp
        tests/ut/test_lock_meta_data.cpp
        tests/ut/test_request.cpp tests/ut/test_promise.cpp)

add_executable(test_actor_system
        tests/ft/test_actor_system.cpp)

if(CMAKE_CXX_STANDARD EQUAL 20)
    add_executable(test_coro_actor tests/ft/test_coro_timer.cpp)
endif()

add_executable(test_async tests/ft/test_async.cpp)

add_executable(test_ping_pong
        tests/ft/test_ping_pong.cpp)

#add_executable(test_job_queue
#        tests/ft/test_job_queue.cpp
#        third-party/nanobench.h
#        tests/ut/nanobench.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(nano_caf-test nano_caf pthread atomic)
    target_link_libraries(test_actor_system nano_caf pthread atomic)
    if(CMAKE_CXX_STANDARD EQUAL 20)
    target_link_libraries(test_coro_actor nano_caf pthread atomic)
    endif()
    target_link_libraries(test_ping_pong nano_caf pthread atomic)
    target_link_libraries(test_async nano_caf pthread atomic)
    #target_link_libraries(test_job_queue nano_caf pthread atomic)
else()
    target_link_libraries(nano_caf-test nano_caf)
    target_link_libraries(test_actor_system nano_caf)
    if(CMAKE_CXX_STANDARD EQUAL 20)
    target_link_libraries(test_coro_actor nano_caf)
    endif()
    target_link_libraries(test_ping_pong nano_caf)
    target_link_libraries(test_async nano_caf)
    #target_link_libraries(test_job_queue nano_caf)
endif()
