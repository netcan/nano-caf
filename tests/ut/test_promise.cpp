//
// Created by Darwin Yuan on 2020/9/21.
//

#include <catch.hpp>
#include <nano-caf/core/await/promise.h>
#include <nano-caf/core/msg/make_message.h>

namespace {
   using namespace NANO_CAF_NS;

   SCENARIO("promise") {
      cancellable_repository repository;
      promise<int> p;
      auto future = p.get_future(repository);
      REQUIRE(future.valid());

      GIVEN("an unready future") {
         std::optional<int> value_set{};
         WHEN("get an awaiter") {
            auto awaiter = future.then([&](int value) { value_set = value; }, [](status_t){});
            THEN("the awaiter should be valid") {
               REQUIRE(awaiter.valid());
            }
            THEN("the callback is not called") {
               REQUIRE(!value_set);
            }
            AND_WHEN("the promise is set") {
               intrusive_actor_ptr null_actor;
               p.set_value(10, null_actor);
               THEN("the awaiter should be valid") {
                  REQUIRE(awaiter.valid());
               }
               THEN("the repository should not be empty") {
                  REQUIRE_FALSE(repository.empty());
               }
               p.get_promise_done_notifier()->on_promise_done();
               THEN("the value should be set") {
                  REQUIRE(value_set.has_value());
               }
               THEN("the awaiter should not be valid") {
                  REQUIRE_FALSE(awaiter.valid());
               }
               THEN("the repository should be empty") {
                  REQUIRE(repository.empty());
               }
            }
         }
      }
   }
}