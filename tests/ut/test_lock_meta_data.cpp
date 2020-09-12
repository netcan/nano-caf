////
//// Created by Darwin Yuan on 2020/8/5.
////
//
//#include <catch.hpp>
//#include <nano-caf/util/macro_lock_meta_data.h>
//
//namespace {
//   using namespace NANO_CAF_NS;
//
//   __CUB_lock_meta_table(Foo,
//       (i_value,     int),
//       (single_elem, int [1]),
//       (c_array10,   char[10]),
//       (c_array3,    char[3]),
//       (i_array5,    int [5]),
//       (c_value,     char)
//   );
//
//   TEST_CASE("before set value, all fields are not present") {
//      Foo foo;
//      REQUIRE(!foo.i_value__present());
//      REQUIRE(!foo.single_elem__present());
//      REQUIRE(!foo.c_array10__present());
//      REQUIRE(!foo.c_array3__present());
//      REQUIRE(!foo.i_array5__present());
//   }
//
//   TEST_CASE("should be able to set the value of a simple type") {
//      Foo foo;
//      foo.i_value(10);
//
//      THEN("it becomes present") {
//         REQUIRE(foo.i_value__present());
//      }
//      THEN("should be able to get its value") {
//         REQUIRE(foo.i_value() == 10);
//      }
//      THEN("should be able to get its value by visitor") {
//         foo.i_value([](auto value) {
//            REQUIRE(value == 10);
//            value = 10;
//         });
//      }
//      THEN("should be able to modify its value by visitor") {
//         foo.i_value__modify([](auto& value) {
//            REQUIRE(value == 10);
//            value = 100;
//         });
//
//         THEN("the value should been altered") {
//            REQUIRE(foo.i_value() == 100);
//         }
//      }
//   }
//
//   TEST_CASE("should be able to set the value of an array type") {
//      Foo foo;
//      foo.i_array5({1,2,3});
//
//      THEN("it should become present") {
//         REQUIRE(foo.i_array5__present());
//      }
//
//      THEN("should be able to read it value by get") {
//         auto&& [array, size] = foo.i_array5();
//         REQUIRE(size == 3);
//         REQUIRE(array[0] == 1);
//         REQUIRE(array[1] == 2);
//         REQUIRE(array[2] == 3);
//      }
//
//      THEN("should be able to read its value by lambda") {
//         foo.i_array5([](auto array, auto size) {
//            REQUIRE(size == 3);
//            REQUIRE(array[0] == 1);
//            REQUIRE(array[1] == 2);
//            REQUIRE(array[2] == 3);
//         });
//      }
//
//      THEN("should be able to modify its value by lambda") {
//         foo.i_array5__modify([](auto array, auto& size) {
//            REQUIRE(size == 3);
//            array[0] = 4;
//            array[1] = 5;
//            size = 2;
//         });
//
//         AND_THEN("the altered value should be able to read") {
//            auto&& [array, size] = foo.i_array5();
//            REQUIRE(size == 2);
//            REQUIRE(array[0] == 4);
//            REQUIRE(array[1] == 5);
//         }
//         AND_THEN("the altered value should be able to read by lambda") {
//            foo.i_array5([](auto array, auto size) {
//               REQUIRE(size == 2);
//               REQUIRE(array[0] == 4);
//               REQUIRE(array[1] == 5);
//            });
//         }
//         WHEN("access a non-present value with lambda") {
//            auto result = foo.c_value(
//               [](auto) {
//                  return true;
//               },
//               [](){
//                  return false;
//               });
//            THEN("should return false") {
//               REQUIRE_FALSE(result);
//            }
//         }
//      }
//   }
//}