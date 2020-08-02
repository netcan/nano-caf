//
// Created by Darwin Yuan on 2020/7/23.
//

#include <catch.hpp>
#include <nano-caf/core/actor/drr_cached_queue.h>
#include <nano-caf/core/msg/make_message.h>
#include "test_msgs.h"

namespace {
   using namespace NANO_CAF_NS;

   SCENARIO("drr_cached_queue consume with resume") {
      drr_cached_queue queue{};

      GIVEN("a queue with 2 elements") {
         task_list list{};
         list.push_back(make_message<test_message>(1));
         list.push_back(make_message<test_message>(2));
         queue.append_list(list);
         THEN("the queue should not be empty now") {
            REQUIRE_FALSE(queue.empty());
         }
         THEN("if consume 2 element once") {
            uint32_t times = 0;
            auto result = queue.new_round(2, [&](const message& elem) noexcept  {
               times++;
               return task_result::resume; });
            THEN("should consume 2 elements") {
               REQUIRE(result == new_round_result{.consumed_items = 2, .stop_all = false});
               REQUIRE(times == 2);
            }
            THEN("the queue should be empty now") {
               REQUIRE(queue.empty());
            }
         }

         AND_WHEN("consume 1 ") {
            auto value = 0;
            auto l = [&](const message& elem) noexcept  {
               value = elem.body<test_message>()->value;
               return task_result::resume; };
            auto result = queue.new_round(1, l);
            THEN("should consume the 1st element") {
               REQUIRE(result == new_round_result{.consumed_items = 1, .stop_all = false});
               REQUIRE(value == 1);
            }
            AND_THEN("consume 1 again") {
               auto result = queue.new_round(1, l);
               THEN("should consume the 2nd element") {
                  REQUIRE(result == new_round_result{.consumed_items = 1, .stop_all = false});
                  REQUIRE(value == 2);
               }
               AND_THEN("consume 1 again") {
                  auto result = queue.new_round(1, l);
                  THEN("should consume nothing") {
                     REQUIRE(result == new_round_result{.consumed_items = 0, .stop_all = false});
                  }
               }
            }
         }
      }
   }

   SCENARIO("drr_cached_queue consume with skip") {
      drr_cached_queue queue{};
      task_list list{};
      list.push_back(make_message<test_message>(1));
      list.push_back(make_message<test_message>(2));
      queue.append_list(list);

      THEN("if consume 2 element once") {
         uint32_t times = 0;
         auto result = queue.new_round(2, [&](const message& elem) noexcept  {
            times++;
            return task_result::skip; });
         THEN("should consume 0 elements") {
            REQUIRE(result == new_round_result{.consumed_items = 0, .stop_all = false});
            REQUIRE(times == 2);
         }
         THEN("the queue should not be empty now") {
            REQUIRE_FALSE(queue.empty());
         }
         THEN("even consume it with 0 quota") {
            uint32_t times = 0;
            auto result = queue.new_round(0, [&](const message& elem) noexcept  {
               times++;
               return task_result::resume; });
            THEN("should consume 2 elements") {
               REQUIRE(result == new_round_result{.consumed_items = 2, .stop_all = false});
               REQUIRE(times == 2);
            }
            THEN("the queue should be empty now") {
               REQUIRE(queue.empty());
            }
         }
      }
   }

   SCENARIO("drr_cached_queue consume with skip once") {
      drr_cached_queue queue{};
      task_list list{};
      list.push_back(make_message<test_message>(1));
      list.push_back(make_message<test_message>(2));
      queue.append_list(list);

      THEN("if consume 2 element once") {
         uint32_t times = 0;
         auto result = queue.new_round(1, [&](const message& elem) noexcept  {
            times++;
            return task_result::skip; });
         THEN("should consume 0 elements") {
            REQUIRE(result == new_round_result{.consumed_items = 0, .stop_all = false});
            REQUIRE(times == 2);
         }
         THEN("the queue should not be empty now") {
            REQUIRE_FALSE(queue.empty());
         }
         THEN("even consume it with 0 quota") {
            uint32_t times = 0;
            auto result = queue.new_round(0, [&](const message& elem) noexcept  {
               times++;
               return task_result::resume; });
            THEN("should consume 1 elements") {
               REQUIRE(result == new_round_result{.consumed_items = 1, .stop_all = false});
               REQUIRE(times == 1);
            }
            THEN("the queue should not be empty now") {
               REQUIRE_FALSE(queue.empty());
            }
         }
      }
   }

   SCENARIO("drr_cached_queue consume with stop") {
      drr_cached_queue queue{};
      task_list list{};
      list.push_back(make_message<test_message>(1));
      list.push_back(make_message<test_message>(2));
      list.push_back(make_message<test_message>(3));
      queue.append_list(list);

      THEN("if consume 3 element once") {
         uint32_t times = 0;
         auto result = queue.new_round(3, [&](const message& elem) noexcept  {
            times++;
            return task_result::done; });
         THEN("should consume 1 element") {
            REQUIRE(result == new_round_result{.consumed_items = 1, .stop_all = true});
            REQUIRE(times == 1);
         }
         THEN("the queue should not be empty now") {
            REQUIRE_FALSE(queue.empty());
         }
         THEN("even consume it with 0 quota") {
            uint32_t times = 0;
            auto result = queue.new_round(0, [&](const message& elem) noexcept  {
               times++;
               return task_result::resume; });
            THEN("should consume the last element") {
               REQUIRE(result == new_round_result{.consumed_items = 2, .stop_all = false});
               REQUIRE(times == 2);
            }
            THEN("the queue should be empty now") {
               REQUIRE(queue.empty());
            }
         }
      }
   }

   SCENARIO("drr_cached_queue consume with stop all") {
      drr_cached_queue queue{};
      task_list list{};
      list.push_back(make_message<test_message>(1));
      list.push_back(make_message<test_message>(2));
      list.push_back(make_message<test_message>(3));
      queue.append_list(list);

      THEN("if consume 3 element once") {
         uint32_t times = 0;
         auto result = queue.new_round(3, [&](const message& elem) noexcept  {
            times++;
            return task_result::done; });
         THEN("should consume 1 elements") {
            REQUIRE(result == new_round_result{.consumed_items = 1, .stop_all = true});
            REQUIRE(times == 1);
         }
         THEN("the queue should not be empty now") {
            REQUIRE_FALSE(queue.empty());
         }
         THEN("even consume it with 0 quota") {
            uint32_t times = 0;
            auto result = queue.new_round(0, [&](const message& elem) noexcept  {
               times++;
               return task_result::resume; });
            THEN("should consume the rest element") {
               REQUIRE(result == new_round_result{.consumed_items = 2, .stop_all = false});
               REQUIRE(times == 2);
            }
            THEN("the queue should be empty now") {
               REQUIRE(queue.empty());
            }
         }
      }
   }

   SCENARIO("drr_cached_queue increase deficit") {
      drr_cached_queue queue{};
      task_list list{};
      list.push_back(make_message<test_message>(1));
      list.push_back(make_message<test_message>(2));
      list.push_back(make_message<test_message>(3));
      queue.append_list(list);

      WHEN("increase 2 deficit") {
         queue.inc_deficit(2);

         THEN("even consume it with 0 quota") {
            uint32_t times = 0;
            auto result = queue.new_round(0, [&](const message& elem) noexcept  {
               times++;
               return task_result::resume; });
            THEN("should consume the rest element") {
               REQUIRE(result == new_round_result{.consumed_items = 2, .stop_all = false});
               REQUIRE(times == 2);
            }
         }
      }

      WHEN("increase 1 deficit") {
         queue.inc_deficit(1);

         THEN("even consume it with 0 quota") {
            uint32_t times = 0;
            auto result = queue.new_round(0, [&](const message& elem) noexcept  {
               times++;
               return task_result::resume; });
            THEN("should consume the rest element") {
               REQUIRE(result == new_round_result{.consumed_items = 1, .stop_all = false});
               REQUIRE(times == 1);
            }
         }
      }
   }

   SCENARIO("drr_cached_queue increase deficit on a empty list") {
      drr_cached_queue queue{};
      queue.inc_deficit(2);
      task_list list{};
      list.push_back(make_message<test_message>(1));
      list.push_back(make_message<test_message>(2));
      list.push_back(make_message<test_message>(3));
      queue.append_list(list);

      THEN("even consume it with 0 quota") {
         uint32_t times = 0;
         auto result = queue.new_round(0, [&](const message &elem) noexcept {
            times++;
            return task_result::resume;
         });
         THEN("should consume nothing") {
            REQUIRE(result == new_round_result{.consumed_items = 0, .stop_all = false});
            REQUIRE(times == 0);
         }
      }
   }

}