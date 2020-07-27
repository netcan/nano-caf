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
        third-party/catch.hpp tests/ut/test_lifo_inbox.cpp include/nano-caf/util/disable_copy.h include/nano-caf/core/actor/lifo_inbox.h include/nano-caf/core/actor/message_element.h tests/ut/catch.cpp src/core/actor/lifo_inbox.cpp include/nano-caf/core/actor/actor_inbox.h src/core/actor/actor_inbox.cpp include/nano-caf/core/actor/actor_storage.h include/nano-caf/core/thread_safe_list.h include/nano-caf/core/spin_lock.h include/nano-caf/core/actor/message_id.h include/nano-caf/core/actor/task_list.h include/nano-caf/core/actor/drr_cached_queue.h tests/ut/test_task_list.cpp src/core/actor/task_list.cpp src/core/actor/ddr_cached_queue.cpp include/nano-caf/core/new_round_result.h tests/ut/test_drr_cached_queue.cpp tests/ut/test_actor_inbox.cpp include/nano-caf/core/resumable.h include/nano-caf/core/actor/sched_actor.h src/core/actor/sched_actor.cpp include/nano-caf/util/intrusive_ptr.h include/nano-caf/core/actor/actor_control_block.h src/core/actor/actor_control_block.cpp include/nano-caf/core/cache_line_size.h include/nano-caf/core/exeution_unit.h tests/ut/test_sched_actor.cpp include/nano-caf/core/worker.h src/core/worker.cpp tests/ut/test_worker.cpp include/nano-caf/core/actor/make_actor.h include/nano-caf/core/coordinator.h src/core/coordinator.cpp src/core/actor_system.cpp include/nano-caf/core/actor/actor_handle.h src/core/actor/actor_handle.cpp tests/ut/test_actor_system.cpp include/nano-caf/core/actor/exit_reason.h include/nano-caf/util/list_element.h include/nano-caf/core/actor/enq_result.h include/nano-caf/core/actor/actor.h include/nano-caf/core/actor/intrusive_actor_ptr.h include/nano-caf/core/actor_context.h src/core/actor/actor_context.cpp include/nano-caf/core/actor/wait_result.h include/nano-caf/core/await/awaitable_object.h include/nano-caf/core/await/future.h include/nano-caf/util/callable_trait.h)