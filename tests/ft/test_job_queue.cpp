//
// Created by Darwin Yuan on 2020/8/3.
//

#include <nano-caf/core/double_end_list.h>
#include <iostream>
#include <nanobench.h>

using namespace NANO_CAF_NS;

struct job : double_end_list_elem {
   job(int value) : value{value} {}
   int value;

   auto to_value_ptr() -> void* override {
      return (void*)this;
   }
};

struct job2 : list_element {
   job2(int value) : value{value} {}
   int value;

   auto to_value_ptr() -> void* override {
      return (void*)this;
   }
};

const unsigned long total = 10000;

auto double_end_list_one_round() -> void {
   double_end_list list{};
   bool started = false;
   std::mutex mutex;
   std::condition_variable cv;

   auto l = [&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&] { return started; });
      }

      int i = 0;
      while (1) {
         auto p = list.pop_front();
         if(p != nullptr) {
            delete p;
            if(++i == total/2) break;
         }
      }
   };

   std::thread reader(l);
   std::thread reader2(l);

   std::thread writer([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      auto half = total/2;
      for(int i=0; i<half; i++) {
         list.enqueue(new job{i});
      }
   });

   std::thread writer2([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      for(int i=total/2; i<total; i++) {
         list.enqueue(new job{i});
      }
   });

   {
      std::unique_lock lock{mutex};
      started = true;
      cv.notify_all();
   }

   writer.join();
   writer2.join();
   reader.join();
   reader2.join();
}

auto thread_safe_list_one_round() -> void {
   thread_safe_list list{};
   bool started = false;
   std::mutex mutex;
   std::condition_variable cv;

   auto l = [&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      int i = 0;
      while (1) {
         auto p = list.dequeue<job2>();
         if(p != nullptr) {
            delete p;
            if(++i == total/2) break;
         }
      }
   };

   std::thread reader(l);
   std::thread reader2(l);

   std::thread writer([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      auto half = total/2;
      for(int i=0; i<half; i++) {
         list.enqueue(new job2{i});
      }
   });

   std::thread writer2([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      for(int i=total/2; i<total; i++) {
         list.enqueue(new job2{i});
      }
   });

   {
      std::unique_lock lock{mutex};
      started = true;
      cv.notify_all();
   }

   writer.join();
   writer2.join();
   reader.join();
   reader2.join();
}

auto double_end_list_test() -> void {
   ankerl::nanobench::Bench().minEpochIterations(109).run("double-end-list", [] {
      double_end_list_one_round();
   });
}

auto thread_safe_list_test() -> void {
   ankerl::nanobench::Bench().minEpochIterations(109).run("thread-safe-list", [] {
      thread_safe_list_one_round();
   });
}

int main() {
   double_end_list_test();
   thread_safe_list_test();
}
