//
// Created by Darwin Yuan on 2020/8/8.
//

#include <catch.hpp>
#include <nano-caf/core/msg/request.h>
#include <nano-caf/core/actor/type_actor_handle.h>

namespace {
   using namespace NANO_CAF_NS;

   __CAF_actor_interface(media_session,
       (open,  (const long&) -> long),
       (close, (int) -> void)
   );

   struct not_atom {};
   struct fake_atom : atom_signature {};

   template<typename  T> struct S;

   //S<detail::method_atoms<media_session>> s;

   TEST_CASE("actor interface") {
      REQUIRE(2 == media_session::total_methods);
      REQUIRE(std::is_same_v<type_list<media_session::open_atom, long>,
         media_session::open_atom::type::pattern_type>);
      REQUIRE(std::is_same_v<type_list<long>, media_session::open_atom::type::args_type>);
      REQUIRE(std::is_same_v<type_list<long>, media_session::open_atom::type::args_type>);

      type_actor_handle<media_session> handle;

      handle.send(media_session::open, (long)10);
   }
}