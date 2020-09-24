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
            [&](media_session::empty) -> auto {
               std::cout << "empty received" << std::endl;
               return std::make_shared<int>(1234);
            },
            [&](exit_msg_atom, exit_reason) {
               std::cout << "exit received" << std::endl;
            },
         };
      }
   };


   using namespace std::chrono_literals;
   struct ctrl_actor : behavior_based_actor {
      typed_actor_handle<media_session> session_actor;
      auto on_init() -> void override {
         session_actor = spawn_typed_actor<media_session, media_session_actor>();
      }

      auto get_behavior() -> behavior override {
         return {
            [&, this](test_message_atom, const int &amount) {
               request<media_session::open>(session_actor, static_cast<long>(amount))
                  .then(
                     [this](auto result) {
                        std::cout << "success = " << result << std::endl;
                        exit(exit_reason::normal);
                     },
                     [](auto failure) {
                        std::cout << "failed = " << failure << std::endl;
                     })
                  .time_guard(1ms);
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
      me.release();
      system.shutdown();
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
         [](auto) { REQUIRE(false); });

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
         [](auto) { return nullptr; }
         );

      REQUIRE(status_t::ok == me.send<media_session::open>(static_cast<long>(10)));
      REQUIRE(status_t::ok == me.send<media_session::close>(static_cast<long>(20)));
      REQUIRE(status_t::ok == me.exit());

      me.wait_for_exit();
      me.release();
      system.shutdown();
   }
}