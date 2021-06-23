//
// Created by Darwin Yuan on 2020/8/8.
//

#include <catch.hpp>
#include <nano-caf/core/msg/request.h>
#include <nano-caf/core/actor/typed_actor_handle.h>
#include <nano-caf/core/actor/behavior_based_actor.h>
#include <iostream>
#include "test_msgs.h"

namespace {
   using namespace NANO_CAF_NS;

   enum : uint32_t {
      media_session_interface_id = 1
   };

   __CAF_actor_interface(media_session, media_session_interface_id,
       (open,  (const long&) -> long),
       (close, (const long&) -> void),
       (empty, ()            -> std::shared_ptr<int>)
   );

   struct not_atom {};
   struct fake_atom : atom_signature {};

   //S<detail::method_atoms<media_session>> s;

   struct media_session_actor : behavior_based_actor {
      auto get_behavior() -> behavior override {
         return {
            [&](media_session::open, long value) -> long {
               return value + 1;
            },
            [&](media_session::close, long) {
            },
            [&](media_session::empty) -> std::shared_ptr<int> {
               return std::make_shared<int>(1234);
            },
            [&](exit_msg_atom, exit_reason) {
               std::cout << "exit received" << std::endl;
            },
         };
      }
   };


   using namespace std::chrono_literals;
   struct intermediate_actor : behavior_based_actor {
      typed_actor_handle<media_session> session_actor;
      auto on_init() -> void {
         session_actor = spawn_typed_actor<media_session, media_session_actor>();
      }

      auto get_behavior() -> behavior override {
         return {
            [&](media_session::open, long value) -> future<long> {
               return request<media_session::open>(session_actor, value);
            },
            [&](media_session::close, long value) -> future<void> {
               return request<media_session::close>(session_actor, value);
            },
            [&](media_session::empty) -> future<std::shared_ptr<int>> {
               return request<media_session::empty>(session_actor);
            },
            [&](exit_msg_atom, exit_reason) {
               std::cout << "exit received" << std::endl;
            },
         };
      }
   };

   using namespace std::chrono_literals;
   struct ctrl_actor : behavior_based_actor {
      typed_actor_handle<media_session> control_actor;
      auto on_init() -> void {
         control_actor = spawn_typed_actor<media_session, intermediate_actor>();
      }

      auto get_behavior() -> behavior override {
         return {
            [this](test_message_atom, int value) {
               request<media_session::open>(control_actor, static_cast<long>(value))
                  .then([this](auto value) {
                     CAF_INFO("open {}", value);
                     return request<media_session::close>(control_actor, static_cast<long>(0));
                  })
                  .then([this]{
                     CAF_INFO("exit");
                     exit(exit_reason::normal);
                  });
            },
            [&](media_session::close, long value) {
               request<media_session::close>(control_actor, value).then([this] {
                  exit(exit_reason::normal);
               });
            },
            [&](exit_msg_atom, exit_reason) {
               std::cout << "exit received" << std::endl;
            },
         };
      }
   };

   TEST_CASE("inter-actor request") {
      actor_system system{1};

      auto me = system.spawn<ctrl_actor>();

      REQUIRE(me.send<test_message>(12) == status_t::ok);

      me.wait_for_exit();
      system.shutdown();
   }

   TEST_CASE("inter actor interface") {
      actor_system system{1};
      REQUIRE(system.get_num_of_actors() == 0);

      SPDLOG_INFO("inter actor interface");
      using namespace std::chrono_literals;

      typed_actor_handle<media_session> me = system.spawn_typed_actor<media_session, intermediate_actor>();
      me.request<media_session::open>(static_cast<long>(10)).wait().match(
         [](auto result) { REQUIRE(result == 11); },
         [](status_t failure) {
            CAF_INFO("failed: {}", failure);
            REQUIRE(false); });

      me.request<media_session::open>(static_cast<long>(20)).wait(0us).match(
         [](auto) { REQUIRE(false); },
         [](auto status) { REQUIRE(status == status_t::timeout); });

      me.request<media_session::open>(static_cast<long>(30)).then(
         [](auto result) { REQUIRE(result == 31); },
         [](auto) {});

      me.request<media_session::close>(static_cast<long>(10)).wait().match(
         []() {},
         [](auto) { REQUIRE(false); });

      me.request<media_session::empty>().wait().match(
         [](auto result) { REQUIRE(*result == 1234);  },
         [](auto) { REQUIRE(false); });

      me.request<media_session::empty>().wait().match(
         [](auto result) { return result; },
         [](auto) { return nullptr; });

      REQUIRE(status_t::ok == me.send<media_session::open>(static_cast<long>(10)));
      REQUIRE(status_t::ok == me.send<media_session::close>(static_cast<long>(20)));
      REQUIRE(status_t::ok == me.exit());

      me.wait_for_exit();
      me.release();
      system.shutdown();
      SPDLOG_INFO("inter actor interface done");
   }

   TEST_CASE("actor interface") {
      REQUIRE(3 == media_session::total_methods);
      REQUIRE(std::is_same_v<type_list<media_session::open, long>,
         media_session::open::type::pattern_type>);
      REQUIRE(std::is_same_v<type_list<long>, media_session::open::type::args_type>);
      REQUIRE(std::is_same_v<type_list<long>, media_session::open::type::args_type>);

      actor_system system{1};
      REQUIRE(system.get_num_of_actors() == 0);

      using namespace std::chrono_literals;

      typed_actor_handle<media_session> me = system.spawn_typed_actor<media_session, media_session_actor>();
      me.request<media_session::open>(static_cast<long>(10)).wait().match(
         [](auto result) { REQUIRE(result == 11); },
         [](status_t failure) {
            CAF_INFO("failed: {}", failure);
            REQUIRE(false); });

      me.request<media_session::open>(static_cast<long>(20)).wait(0us).match(
         [](auto) { REQUIRE(false); },
         [](auto status) { REQUIRE(status == status_t::timeout); });

      me.request<media_session::open>(static_cast<long>(30)).then(
         [](auto result) { REQUIRE(result == 31); },
         [](auto) {});

      me.request<media_session::close>(static_cast<long>(10)).wait().match(
         []() {},
         [](auto) { REQUIRE(false); });

      me.request<media_session::empty>().wait().match(
         [](auto result) { REQUIRE(*result == 1234);  },
         [](auto) { REQUIRE(false); });

      me.request<media_session::empty>().wait().match(
         [](auto result) { return result; },
         [](auto) { return nullptr; });

      REQUIRE(status_t::ok == me.send<media_session::open>(static_cast<long>(10)));
      REQUIRE(status_t::ok == me.send<media_session::close>(static_cast<long>(20)));
      REQUIRE(status_t::ok == me.exit());

      me.wait_for_exit();
      me.release();
      system.shutdown();
   }
}
