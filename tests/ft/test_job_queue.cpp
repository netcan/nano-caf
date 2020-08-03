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

const unsigned long total = 100000;
std::vector<job*> all_jobs;
void init_jobs() {
   all_jobs.reserve(total);
   for(int i=0; i<total; i++) {
      all_jobs.emplace_back(new job{i});
   }
}

std::vector<job2*> all_jobs2;
void init_jobs2() {
   all_jobs2.reserve(total);
   for(int i=0; i<total; i++) {
      all_jobs2.emplace_back(new job2{i});
   }
}

auto double_end_list_one_round() -> void {
   double_end_list list{};
   bool started = false;
   std::mutex mutex;
   std::condition_variable cv;

   std::thread reader([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&] { return started; });
      }

      int i = 0;
      while (1) {
         auto p = list.pop_front();
         if(p != nullptr) {
            if(++i == total/2) break;
         }
      }
   });

   std::thread reader2([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&] { return started; });
      }

      int i = 0;
      while (1) {
         auto p = list.pop_front();
         if(p != nullptr) {
            if(++i == total/2) break;
         }
      }
   });

   std::thread writer([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      auto half = total/2;
      for(int i=0; i<half; i++) {
         list.enqueue(all_jobs[i]);
      }
   });

   std::thread writer2([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      for(int i=total/2; i<total; i++) {
         list.enqueue(all_jobs[i]);
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

   std::thread reader([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      int i = 0;
      while (1) {
         auto p = list.dequeue<job2>();
         if(p != nullptr) {
            if(++i == total/2) break;
         }
      }
   });

   std::thread reader2([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      int i = 0;
      while (1) {
         auto p = list.dequeue<job2>();
         if(p != nullptr) {
            if(++i == total/2) break;
         }
      }
   });

   std::thread writer([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      auto half = total/2;
      for(int i=0; i<half; i++) {
         list.enqueue(all_jobs2[i]);
      }
   });

   std::thread writer2([&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      for(int i=total/2; i<total; i++) {
         list.enqueue(all_jobs2[i]);
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
   init_jobs();
   init_jobs2();
   double_end_list_test();
   thread_safe_list_test();
}
