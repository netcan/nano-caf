//
// Created by Darwin Yuan on 2020/8/8.
//

#include <catch.hpp>
#include <nano-caf/core/msg/request.h>

namespace {
   using namespace NANO_CAF_NS;

   __CAF_actor_interface(media_session,
       (open,  (int&) -> long),
       (close, (int) -> void)
   );

   struct not_atom {};
   struct fake_atom : atom_signature {};

   template<typename ACTOR_INTERFACE>
   struct type_actor_handle {
      template<typename METHOD_ATOM, typename ... Args, typename = std::enable_if_t<is_msg_atom<METHOD_ATOM>>>
      auto send(METHOD_ATOM atom, Args&& ... args) {
         static_assert(type_list_exists<METHOD_ATOM, detail::method_atoms<ACTOR_INTERFACE>>, "method does not exist");
      }
   };

   template<typename  T> struct S;

   //S<detail::method_atoms<media_session>> s;

   TEST_CASE("actor interface") {
      REQUIRE(2 == media_session::total_methods);
      REQUIRE(std::is_same_v<type_list<media_session::open_atom, int>, media_session::open_atom::type::pattern_type>);
      REQUIRE(std::is_same_v<type_list<int>, media_session::open_atom::type::args_type>);
      REQUIRE(std::is_same_v<type_list<int>, media_session::open_atom::type::args_type>);

      type_actor_handle<media_session> handle;

      handle.send(media_session::open);
   }
}