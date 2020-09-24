////
//// Created by Darwin Yuan on 2020/9/21.
////
//
//#include <catch.hpp>
//#include <nano-caf/core/await/promise.h>
//#include <nano-caf/core/await/multi_future.h>
//
//namespace {
//   using namespace NANO_CAF_NS;
//
//   struct my_on_actor_context : on_actor_context {
//      virtual auto start_timer(timer_spec const& spec, bool periodic, std::shared_ptr<timeout_callback_t> callback) -> result_t<timer_id_t> override {
//         return status_t::failed;
//      }
//      virtual auto stop_timer(timer_id_t timer_id) -> void override {}
//   };
//
//   SCENARIO("promise") {
//      my_on_actor_context context;
//      promise<int> p;
//      auto future = p.get_future(context);
//      REQUIRE(future.valid());
//
//      GIVEN("an unready future") {
//         std::optional<int> value_set{};
//         std::optional<status_t> failure_set{};
//         WHEN("get an awaiter") {
//            auto awaiter = future.then(
//               [&](int value) { value_set = value; },
//               [&](status_t failure){ failure_set = failure; });
//            THEN("the awaiter should be valid") {
//               REQUIRE(awaiter.valid());
//            }
//            THEN("the callback is not called") {
//               REQUIRE(!value_set);
//            }
//            AND_WHEN("the awaiter is cancelled") {
//               awaiter.cancel(status_t::timeout);
//               THEN("the failure should be set") {
//                  REQUIRE(failure_set.has_value());
//                  REQUIRE(*failure_set == status_t::timeout);
//               }
//               THEN("the awaiter should not be valid") {
//                  REQUIRE_FALSE(awaiter.valid());
//               }
//               THEN("the repository should be empty") {
//                  REQUIRE(context.empty());
//               }
//            }
//            AND_WHEN("the promise is set") {
//               intrusive_actor_ptr null_actor;
//               p.set_value(10, null_actor);
//               THEN("the awaiter should be valid") {
//                  REQUIRE(awaiter.valid());
//               }
//               THEN("the repository should not be empty") {
//                  REQUIRE_FALSE(context.empty());
//               }
//               p.get_promise_done_notifier()->on_promise_done();
//               THEN("the value should be set") {
//                  REQUIRE(value_set.has_value());
//               }
//               THEN("the awaiter should not be valid") {
//                  REQUIRE_FALSE(awaiter.valid());
//               }
//               THEN("the repository should be empty") {
//                  REQUIRE(context.empty());
//               }
//            }
//         }
//      }
//   }
//
//   SCENARIO("expired promise") {
//      my_on_actor_context context;
//      promise<int> p;
//      auto future = p.get_future(context);
//      intrusive_actor_ptr null_actor;
//      p.set_value(10, null_actor);
//      p.get_promise_done_notifier()->on_promise_done();
//      WHEN("get an awaiter") {
//         std::optional<int> value_set{};
//         std::optional<status_t> failure_set{};
//         auto awaiter = future.then(
//            [&](int value) { value_set = value; },
//            [&](status_t failure) { failure_set = failure; });
//         THEN("the awaiter should not be valid") {
//            REQUIRE_FALSE(awaiter.valid());
//         }
//         THEN("the callback is called") {
//            REQUIRE(value_set.has_value());
//            REQUIRE(*value_set == 10);
//         }
//      }
//   }
//
//   SCENARIO("multi-future") {
//      my_on_actor_context context;
//      promise<int> p1;
//      auto future1 = p1.get_future(context);
//
//      promise<short> p2;
//      auto future2 = p2.get_future(context);
//
//      std::optional<int> result_set;
//      auto awaiter = multi_future<int, short>{context, future1, future2}
//      .then([&](int i, short j) { result_set = i + j; },
//            [](status_t) {});
//
//      REQUIRE(!result_set.has_value());
//
//      intrusive_actor_ptr null_actor;
//      p1.set_value(10, null_actor);
//      p1.get_promise_done_notifier()->on_promise_done();
//
//      REQUIRE(!result_set.has_value());
//
//      p2.set_value(5, null_actor);
//      p2.get_promise_done_notifier()->on_promise_done();
//
//      REQUIRE(result_set.has_value());
//
//      REQUIRE(*result_set == 15);
//
//      REQUIRE_FALSE(awaiter.valid());
//      REQUIRE(context.empty());
//   }
//
//   SCENARIO("partial multi-future") {
//      my_on_actor_context context;
//      promise<int> p1;
//      auto future1 = p1.get_future(context);
//
//      intrusive_actor_ptr null_actor;
//      p1.set_value(10, null_actor);
//      p1.get_promise_done_notifier()->on_promise_done();
//
//      promise<short> p2;
//      auto future2 = p2.get_future(context);
//
//      std::optional<int> result_set;
//      auto awaiter = multi_future<int, short>{context, future1, future2}
//         .then([&](int i, short j) { result_set = i + j; },
//               [](status_t) {});
//
//      REQUIRE(!result_set.has_value());
//
//      p2.set_value(5, null_actor);
//      p2.get_promise_done_notifier()->on_promise_done();
//
//      REQUIRE(result_set.has_value());
//
//      REQUIRE(*result_set == 15);
//
//      REQUIRE_FALSE(awaiter.valid());
//      REQUIRE(context.empty());
//   }
//
//   SCENARIO("late multi-future") {
//      my_on_actor_context context;
//      promise<int> p1;
//      auto future1 = p1.get_future(context);
//
//      intrusive_actor_ptr null_actor;
//      p1.set_value(10, null_actor);
//      p1.get_promise_done_notifier()->on_promise_done();
//
//      promise<short> p2;
//      auto future2 = p2.get_future(context);
//
//      p2.set_value(5, null_actor);
//      p2.get_promise_done_notifier()->on_promise_done();
//
//      std::optional<int> result_set;
//      auto awaiter = multi_future<int, short>{context, future1, future2}
//         .then([&](int i, short j) { result_set = i + j; },
//               [](status_t) {});
//
//      REQUIRE(result_set.has_value());
//
//      REQUIRE(*result_set == 15);
//
//      REQUIRE_FALSE(awaiter.valid());
//      REQUIRE(context.empty());
//   }
//
//   SCENARIO("cancel multi-future") {
//      my_on_actor_context context;
//      promise<int> p1;
//      auto future1 = p1.get_future(context);
//
//      intrusive_actor_ptr null_actor;
//      p1.set_value(10, null_actor);
//      p1.get_promise_done_notifier()->on_promise_done();
//
//      promise<short> p2;
//      auto future2 = p2.get_future(context);
//
//      std::optional<int> result_set;
//      std::optional<status_t> failure_set;
//      auto awaiter = multi_future<int, short>{context, future1, future2}
//         .then([&](int i, short j) { result_set = i + j; },
//               [&](status_t status) { failure_set = status; });
//
//      awaiter.cancel(status_t::cancelled);
//
//      REQUIRE(!result_set.has_value());
//      REQUIRE(failure_set.has_value());
//      REQUIRE(*failure_set == status_t::cancelled);
//
//      REQUIRE_FALSE(awaiter.valid());
//      REQUIRE(context.empty());
//   }
//}