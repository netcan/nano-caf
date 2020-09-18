//
// Created by Darwin Yuan on 2020/8/3.
//

#include <catch.hpp>
#include <nano-caf/core/thread_pool/double_end_list.h>

namespace {
   using namespace NANO_CAF_NS;

   struct job : double_end_list_elem {
      job(int value) : value{value} {}
      int value;

      auto to_value_ptr() -> void* override {
         return reinterpret_cast<void*>(this);
      }
   };

   SCENARIO("double end queue") {
      double_end_list list{};

      SECTION("an empty list should be empty") {
         REQUIRE(list.empty());
      }

      WHEN("enqueue a elem, should return ok") {
         REQUIRE(enq_result::ok == list.enqueue(new job{8}));
         AND_THEN("the list is not empty") {
            REQUIRE_FALSE(list.empty());
         }
         AND_THEN("the elem could be take out") {
            auto elem = std::unique_ptr<job>(list.dequeue<job>());
            REQUIRE(elem != nullptr);
            REQUIRE(elem->value == 8);

            AND_THEN("the list becomes empty again") {
               REQUIRE(list.empty());
            }
         }
      }

      WHEN("enqueue many elems, should return ok") {
         REQUIRE(enq_result::ok == list.enqueue(new job{1}));
         REQUIRE(enq_result::ok == list.enqueue(new job{2}));
         REQUIRE(enq_result::ok == list.enqueue(new job{3}));
         AND_THEN("the list is not empty") {
            REQUIRE_FALSE(list.empty());
         }
         AND_THEN("dequeue an elem") {
            auto elem = std::unique_ptr<job>(list.dequeue<job>());
            THEN("should be the 1st one") {
               REQUIRE(elem != nullptr);
               REQUIRE(elem->value == 1);
               AND_WHEN("dequeue an elem again") {
                  auto elem = std::unique_ptr<job>(list.dequeue<job>());
                  THEN("should be the 2nd one") {
                     REQUIRE(elem != nullptr);
                     REQUIRE(elem->value == 2);
                     AND_WHEN("dequeue an elem again") {
                        auto elem = std::unique_ptr<job>(list.dequeue<job>());
                        THEN("should be the 3rd one") {
                           REQUIRE(elem != nullptr);
                           REQUIRE(elem->value == 3);
                           AND_THEN("dequeue an elem again") {
                              auto elem = list.dequeue<job>();
                              THEN("should get a nullptr") {
                                 REQUIRE(elem == nullptr);
                              }
                           }
                           AND_THEN("the list becomes empty again") {
                              REQUIRE(list.empty());
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
}