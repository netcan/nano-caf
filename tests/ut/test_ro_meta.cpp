//
// Created by Darwin Yuan on 2020/8/5.
//

#include <catch.hpp>
#include <nano-caf/util/macro_ro_meta_data.h>

namespace {
   using namespace NANO_CAF_NS;

   struct Foo {
      __CUB_ro_meta_data(
         (int)      i_value,
         (int[1])   single_elem,
         (char[10]) c_array10,
         (char[3])  c_array3,
         (int[5])   i_array5
      );
   };

   struct Foo_Initializer : Foo {
      auto init() -> Foo const& {
         i_value(100);
         single_elem(150);

         c_array10({8, 9});

         char c[]={1,2};
         c_array3({c, 2});

         i_array5([](auto array, auto& size){
            array[0] = 10;
            array[1] = 20;
            array[2] = 30;
            size = 3;
         });

         return *this;
      }
   };

   template<typename T> struct S;
   TEST_CASE("should be able to get value of simple-type") {
      Foo_Initializer initializer;
      auto& foo = initializer.init();

      THEN("should be able to access simple type by lambda") {
         foo.i_value([](auto value) {
            REQUIRE(value == 100);
         });
      }
      THEN("should be able to access array type with 1 elem by lambda") {
         foo.single_elem([](auto value) {
            REQUIRE(value == 150);
         });
      }
      THEN("should be able to access array by lambda") {
         foo.c_array10([](auto array, auto size) {
            REQUIRE(size == 2);
            REQUIRE(array[0] == 8);
            REQUIRE(array[1] == 9);
         });
      }
      THEN("should be able to access pair-constructed array by lambda") {
         foo.c_array3([](auto array, auto size) {
            REQUIRE(size == 2);
            REQUIRE(array[0] == 1);
            REQUIRE(array[1] == 2);
         });
      }
      THEN("should be able to access lambda-constructed array by lambda") {
         foo.i_array5([](auto array, auto size) {
            REQUIRE(size == 3);
            REQUIRE(array[0] == 10);
            REQUIRE(array[1] == 20);
            REQUIRE(array[2] == 30);
         });
      }
      THEN("should be able access array by get") {
         auto [array, size] = foo.c_array10();
         REQUIRE(std::is_same_v<char const*, decltype(array)>);
         REQUIRE(size == 2);
         REQUIRE(array[0] == 8);
         REQUIRE(array[1] == 9);
      }
      THEN("should be able to access simple type by get") {
         REQUIRE(100 == foo.i_value());
      }
      THEN("should be able to access array type with 1 elem by get") {
         REQUIRE(150 == foo.single_elem());
      }
      THEN("should be able to access pair-constructed array by get") {
         auto [array, size] = foo.c_array3();
         REQUIRE(size == 2);
         REQUIRE(array[0] == 1);
         REQUIRE(array[1] == 2);
      }
   }
}