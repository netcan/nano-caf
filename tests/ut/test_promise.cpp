//
// Created by Darwin Yuan on 2020/9/21.
//

#include <catch.hpp>
#include <nano-caf/core/await/promise.h>
#include <nano-caf/core/await/multi_future.h>

namespace {
   using namespace NANO_CAF_NS;

   struct my_on_actor_context : on_actor_context {
      virtual auto start_timer(timer_spec const& spec, bool periodic, std::shared_ptr<timeout_callback_t> callback) -> result_t<timer_id_t> override {
         return status_t::failed;
      }
      virtual auto stop_timer(timer_id_t timer_id) -> void override {}
   };

   SCENARIO("promise") {
      my_on_actor_context context;
      std::optional<promise<int>> p;
      future<int> future{context, [&](auto obj) -> status_t {
         p.emplace(promise<int>{obj});
         return status_t::ok;
      }};

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
                  REQUIRE(context.empty());
               }
            }
            AND_WHEN("the promise is set") {
               intrusive_actor_ptr null_actor;
               p->set_value(10, null_actor);
               THEN("the awaiter should be valid") {
                  REQUIRE(awaiter.valid());
               }
               THEN("the repository should not be empty") {
                  REQUIRE_FALSE(context.empty());
               }
               p->get_promise_done_notifier()->on_promise_done();
               THEN("the value should be set") {
                  REQUIRE(value_set.has_value());
               }
               THEN("the awaiter should not be valid") {
                  REQUIRE_FALSE(awaiter.valid());
               }
               THEN("the repository should be empty") {
                  REQUIRE(context.empty());
               }
            }
         }
      }
   }

   SCENARIO("launch fail single future") {
      my_on_actor_context context;

      future<int> future{context, [&](auto obj) -> status_t {
         return status_t::out_of_mem;
      }};

      WHEN("get an awaiter") {
         std::optional<status_t> failure_set{};
         auto awaiter = future.then(
            [&](int) {},
            [&](status_t cause) { failure_set = cause; });

         THEN("when launch, it failed") {
            REQUIRE(failure_set.has_value());
            REQUIRE(*failure_set == status_t::out_of_mem);
         }

         THEN("awaiter is not valid") {
            REQUIRE_FALSE(awaiter.valid());
         }
      }
   }

   SCENARIO("expired promise") {
      my_on_actor_context context;

      std::optional<promise<int>> p;
      future<int> future{context, [&](auto obj) -> status_t {
         p.emplace(promise<int>{obj});
         return status_t::ok;
      }};

      REQUIRE_FALSE(p.has_value());

      WHEN("get an awaiter") {
         auto awaiter1 = future.then(
            [&](int) {},
            [&](status_t) {});

         THEN("the promise should be launched") {
            REQUIRE(p.has_value());
         }

         intrusive_actor_ptr null_actor;
         p->set_value(10, null_actor);
         p->get_promise_done_notifier()->on_promise_done();

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

   SCENARIO("multi-future") {
      my_on_actor_context context;

      std::optional<promise<int>> p1;
      future<int> future1{context, [&](auto obj) -> status_t {
         p1.emplace(promise<int>{obj});
         return status_t::ok;
      }};

      std::optional<promise<short>> p2;
      future<short> future2{context, [&](auto obj) -> status_t {
         p2.emplace(promise<short>{obj});
         return status_t::ok;
      }};

      std::optional<int> result_set;
      auto awaiter = multi_future<int, short>{context, future1, future2}
      .then([&](int i, short j) { result_set = i + j; },
            [](status_t) {});

      REQUIRE(!result_set.has_value());

      intrusive_actor_ptr null_actor;
      p1->set_value(10, null_actor);
      p1->get_promise_done_notifier()->on_promise_done();

      REQUIRE(!result_set.has_value());

      p2->set_value(5, null_actor);
      p2->get_promise_done_notifier()->on_promise_done();

      REQUIRE(result_set.has_value());

      REQUIRE(*result_set == 15);

      REQUIRE_FALSE(awaiter.valid());
      REQUIRE(context.empty());
   }

   SCENARIO("partial multi-future") {
      my_on_actor_context context;

      std::optional<promise<int>> p1;
      future<int> future1{context, [&](auto obj) -> status_t {
         p1.emplace(promise<int>{obj});
         return status_t::ok;
      }};

      future1.on_succeed([](auto){});

      intrusive_actor_ptr null_actor;
      p1->set_value(10, null_actor);
      p1->get_promise_done_notifier()->on_promise_done();

      std::optional<promise<short>> p2;
      future<short> future2{context, [&](auto obj) -> status_t {
         p2.emplace(promise<short>{obj});
         return status_t::ok;
      }};

      std::optional<int> result_set;
      auto awaiter = multi_future<int, short>{context, future1, future2}
         .then([&](int i, short j) { result_set = i + j; },
               [](status_t) {});

      REQUIRE(!result_set.has_value());

      p2->set_value(5, null_actor);
      p2->get_promise_done_notifier()->on_promise_done();

      REQUIRE(result_set.has_value());

      REQUIRE(*result_set == 15);

      REQUIRE_FALSE(awaiter.valid());
      REQUIRE(context.empty());
   }

   SCENARIO("late multi-future") {
      my_on_actor_context context;

      std::optional<promise<int>> p1;
      future<int> future1{context, [&](auto obj) -> status_t {
         p1.emplace(promise<int>{obj});
         return status_t::ok;
      }};

      future1.on_succeed([](auto){});

      intrusive_actor_ptr null_actor;
      p1->set_value(10, null_actor);
      p1->get_promise_done_notifier()->on_promise_done();

      std::optional<promise<short>> p2;
      future<short> future2{context, [&](auto obj) -> status_t {
         p2.emplace(promise<short>{obj});
         return status_t::ok;
      }};

      future2.on_succeed([](auto){});

      p2->set_value(5, null_actor);
      p2->get_promise_done_notifier()->on_promise_done();

      std::optional<int> result_set;
      auto awaiter = multi_future<int, short>{context, future1, future2}
         .then([&](int i, short j) { result_set = i + j; },
               [](status_t) {});

      REQUIRE(result_set.has_value());

      REQUIRE(*result_set == 15);

      REQUIRE_FALSE(awaiter.valid());
      REQUIRE(context.empty());
   }

   SCENARIO("cancel multi-future") {
      my_on_actor_context context;

      std::optional<promise<int>> p1;
      future<int> future1{context, [&](auto obj) -> status_t {
         p1.emplace(promise<int>{obj});
         return status_t::ok;
      }};

      future1.on_succeed([](auto){});

      intrusive_actor_ptr null_actor;
      p1->set_value(10, null_actor);
      p1->get_promise_done_notifier()->on_promise_done();

      std::optional<promise<short>> p2;
      future<short> future2{context, [&](auto obj) -> status_t {
         p2.emplace(promise<short>{obj});
         return status_t::ok;
      }};

      std::optional<int> result_set;
      std::optional<status_t> failure_set;
      auto awaiter = multi_future<int, short>{context, future1, future2}
         .then([&](int i, short j) { result_set = i + j; },
               [&](status_t status) { failure_set = status; });

      awaiter.cancel(status_t::cancelled);

      REQUIRE(!result_set.has_value());
      REQUIRE(failure_set.has_value());
      REQUIRE(*failure_set == status_t::cancelled);

      REQUIRE_FALSE(awaiter.valid());
      REQUIRE(context.empty());
   }

   SCENARIO("partial failed multi-future") {
      my_on_actor_context context;

      future<int> future1{context, [&](auto obj) -> status_t {
         return status_t::out_of_mem;
      }};

      std::optional<promise<short>> p2;
      future<short> future2{context, [&](auto obj) -> status_t {
         p2.emplace(promise<short>{obj});
         return status_t::ok;
      }};

      std::optional<int> result_set;
      std::optional<status_t> failure_set;
      auto awaiter = multi_future<int, short>{context, future1, future2}
         .then([&](int i, short j) { result_set = i + j; },
               [&](status_t status) { failure_set = status; });

      REQUIRE(!result_set.has_value());
      REQUIRE(failure_set.has_value());
      REQUIRE(*failure_set == status_t::out_of_mem);

      REQUIRE_FALSE(awaiter.valid());
      REQUIRE(context.empty());
   }
}