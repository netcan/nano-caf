////
//// Created by Darwin Yuan on 2020/8/5.
////
//
//#include <catch.hpp>
//#include <nano-caf/util/macro_ro_meta_data.h>
//
//namespace {
//   using namespace NANO_CAF_NS;
//
//   struct S {
//      int a;
//      int b;
//   };
//   __CUB_2_stage_meta_table(Foo_RW, Foo,
//       (i_value,     int),
//       (single_elem, int[1]),
//       (c_array10,   char[10]),
//       (c_array3,    char[3]),
//       (i_array5,    int[5]),
//       (c_value,     char));
//
//
//   TEST_CASE("should be able to get value of simple-type") {
//      Foo_RW foo_rw;
//
//      foo_rw.i_value(100);
//      foo_rw.single_elem(150);
//
//      foo_rw.c_array10({8, 9});
//
//      char c[]={1,2};
//      foo_rw.c_array3({c, 2});
//
//      foo_rw.i_array5__modify([](auto array, auto& size){
//         array[0] = 10;
//         array[1] = 20;
//         array[2] = 30;
//         size = 3;
//      });
//
//      const Foo& foo = foo_rw;
//
//      THEN("should be able to access simple type by lambda") {
//         foo.i_value([](auto value) {
//            REQUIRE(value == 100);
//         });
//      }
//      THEN("should be able to access array type with 1 elem by lambda") {
//         foo.single_elem([](auto value) {
//            REQUIRE(value == 150);
//         });
//      }
//      THEN("should be able to access array by lambda") {
//         foo.c_array10([](auto array, auto size) {
//            REQUIRE(size == 2);
//            REQUIRE(array[0] == 8);
//            REQUIRE(array[1] == 9);
//         });
//      }
//      THEN("should be able to access pair-constructed array by lambda") {
//         foo.c_array3([](auto array, auto size) {
//            REQUIRE(size == 2);
//            REQUIRE(array[0] == 1);
//            REQUIRE(array[1] == 2);
//         });
//      }
//      THEN("should be able to access lambda-constructed array by lambda") {
//         foo.i_array5([](auto array, auto size) {
//            REQUIRE(size == 3);
//            REQUIRE(array[0] == 10);
//            REQUIRE(array[1] == 20);
//            REQUIRE(array[2] == 30);
//         });
//      }
//      THEN("should be able access array by get") {
//         auto [array, size] = foo.c_array10();
//         REQUIRE(std::is_same_v<char const*, decltype(array)>);
//         REQUIRE(size == 2);
//         REQUIRE(array[0] == 8);
//         REQUIRE(array[1] == 9);
//      }
//      THEN("should be able to access simple type by get") {
//         REQUIRE(100 == foo.i_value());
//      }
//      THEN("should be able to access array type with 1 elem by get") {
//         REQUIRE(150 == foo.single_elem());
//      }
//      THEN("should be able to access pair-constructed array by get") {
//         REQUIRE(foo.c_array3__present());
//         auto [array, size] = foo.c_array3();
//         REQUIRE(size == 2);
//         REQUIRE(array[0] == 1);
//         REQUIRE(array[1] == 2);
//      }
//      WHEN("access a non-present value with lambda") {
//         auto result = foo.c_value(
//            [](auto) {
//               return true;
//            },
//            [] {
//               return false;
//            });
//         THEN("should return false") {
//            REQUIRE_FALSE(result);
//         }
//      }
//   }
//}