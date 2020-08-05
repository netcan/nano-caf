//
// Created by Darwin Yuan on 2020/8/5.
//

#include <catch.hpp>
#include <nano-caf/util/macro_lock_meta_data.h>

namespace {
   using namespace NANO_CAF_NS;

   struct Foo {
      __CUB_lock_meta_data(
         (int)      i_value,
         (int[1])   single_elem,
         (char[10]) c_array10,
         (char[3])  c_array3,
         (int[5])   i_array5
      );
   };

   TEST_CASE("before set value, all fields are not present") {
      Foo foo;
      REQUIRE(!foo.i_value_present());
      REQUIRE(!foo.single_elem_present());
      REQUIRE(!foo.c_array10_present());
      REQUIRE(!foo.c_array3_present());
      REQUIRE(!foo.i_array5_present());
   }

   TEST_CASE("should be able to set the value of a simple type") {
      Foo foo;
      foo.i_value(10);

      THEN("it becomes present") {
         REQUIRE(foo.i_value_present());
      }
      THEN("should be able to get its value") {
         REQUIRE(foo.i_value() == 10);
      }
      THEN("should be able to get its value by visitor") {
         foo.i_value([](auto value) {
            REQUIRE(value == 10);
         });
      }
      THEN("should be able to modify its value by visitor") {
         foo.i_value__modify([](auto& value) {
            REQUIRE(value == 10);
            value = 100;
         });

         THEN("the value should been altered") {
            REQUIRE(foo.i_value() == 100);
         }
      }
   }
}