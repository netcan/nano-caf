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
         std::optional<status_t> failure_set{};
         WHEN("get an awaiter") {
            auto awaiter = future.then(
               [&](int value) { value_set = value; },
               [&](status_t failure){ failure_set = failure; });
            THEN("the awaiter should be valid") {
               REQUIRE(awaiter.valid());
            }
            THEN("the callback is not called") {
               REQUIRE(!value_set);
            }
            AND_WHEN("the awaiter is cancelled") {
               awaiter.cancel(status_t::timeout);
               THEN("the failure should be set") {
                  REQUIRE(failure_set.has_value());
                  REQUIRE(*failure_set == status_t::timeout);
               }
               THEN("the awaiter should not be valid") {
                  REQUIRE_FALSE(awaiter.valid());
               }
               THEN("the repository should be empty") {
                  REQUIRE(repository.empty());
               }
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

   SCENARIO("expired promise") {
      cancellable_repository repository;
      promise<int> p;
      auto future = p.get_future(repository);
      intrusive_actor_ptr null_actor;
      p.set_value(10, null_actor);
      p.get_promise_done_notifier()->on_promise_done();
      WHEN("get an awaiter") {
         std::optional<int> value_set{};
         std::optional<status_t> failure_set{};
         auto awaiter = future.then(
            [&](int value) { value_set = value; },
            [&](status_t failure) { failure_set = failure; });
         THEN("the awaiter should not be valid") {
            REQUIRE_FALSE(awaiter.valid());
         }
         THEN("the callback is called") {
            REQUIRE(value_set.has_value());
            REQUIRE(*value_set == 10);
         }
      }
   }
}