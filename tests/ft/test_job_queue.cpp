//
// Created by Darwin Yuan on 2020/8/3.
//

#include <nano-caf/core/thread_pool/double_end_list.h>
#include <iostream>
#include <nanobench.h>
#include <nano-caf/core/thread_pool/lock_free_list.h>
#include <mutex>
#include <condition_variable>

using namespace NANO_CAF_NS;

struct job : double_end_list_elem {
   job(size_t value) : value{value} {}
    size_t value;

   auto to_value_ptr() -> void* override {
      return reinterpret_cast<void*>(this);
   }
};

struct job1 : lock_free_list_elem {
   job1(size_t value) : value{value} {}
    size_t value;

   auto to_value_ptr() -> void* override {
      return reinterpret_cast<void*>(this);
   }
};

struct job2 : list_element {
   job2(size_t value) : value{value} {}
    size_t value;

   auto to_value_ptr() -> void* override {
      return reinterpret_cast<void*>(this);
   }
};

const size_t total = 1000;

auto double_end_list_one_round(size_t number) -> void {
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
            if(++i == total) break;
         }
      }
   };

   std::vector<std::thread> reader;

   for(size_t i = 0; i<number; i++) {
      reader.emplace_back(l);
   }

   auto w = [&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      for(size_t i=0; i<total; i++) {
         list.enqueue(new job{i});
      }
   };

   std::vector<std::thread> writer;
   for(size_t i = 0; i<number; i++) {
      writer.emplace_back(w);
   }


   {
      std::unique_lock lock{mutex};
      started = true;
      cv.notify_all();
   }

   for(size_t i = 0; i<number; i++) {
      writer[i].join();
   }

   for(size_t i = 0; i<number; i++) {
      reader[i].join();
   }
}

auto lock_free_list_one_round(size_t number) -> void {
   lock_free_list list{};

   bool started = false;
   std::mutex mutex;
   std::condition_variable cv;

   auto l = [&](size_t){
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&] { return started; });
      }

      int i = 0;
      while (1) {
         auto p = list.pop_front();
         if(p != nullptr) {
            delete p;
            if(++i == total) return;
         }
      }
   };

   std::vector<std::thread> reader;

   for(size_t i = 0; i<number; i++) {
      reader.emplace_back(l, i);
   }

   auto w = [&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      for(size_t i=0; i<total; i++) {
         auto result = list.enqueue(new job1{i});
         if(result != enq_result::ok) {
            exit(-1);
         }
      }
   };

   std::vector<std::thread> writer;
   for(size_t i = 0; i<number; i++) {
      writer.emplace_back(w);
   }

   {
      std::unique_lock lock{mutex};
      started = true;
      cv.notify_all();
   }

   for(size_t i = 0; i<number; i++) {
      writer[i].join();
   }

   for(size_t i = 0; i<number; i++) {
      reader[i].join();
   }
}

auto thread_safe_list_one_round(size_t number) -> void {
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
            if(++i == total) break;
         }
      }
   };

   std::vector<std::thread> reader;

   for(size_t i = 0; i<number; i++) {
      reader.emplace_back(l);
   }

  auto w = [&]{
      {
         std::unique_lock lock{mutex};
         cv.wait(lock, [&]{ return started; });
      }

      for(size_t i=0; i<total; i++) {
         list.enqueue(new job2{i});
      }
   };

   std::vector<std::thread> writer;
   for(size_t i = 0; i<number; i++) {
      writer.emplace_back(w);
   }

   {
      std::unique_lock lock{mutex};
      started = true;
      cv.notify_all();
   }

   for(size_t i = 0; i<number; i++) {
      writer[i].join();
   }

   for(size_t i = 0; i<number; i++) {
      reader[i].join();
   }
}

auto double_end_list_test(size_t number) -> void {
   ankerl::nanobench::Bench().minEpochIterations(109).run("double-end-list", [=] {
      double_end_list_one_round(number);
   });
}


auto lock_free_list_test(size_t number) -> void {
   ankerl::nanobench::Bench().minEpochIterations(109).run("lock-free-list", [=] {
      lock_free_list_one_round(number);
   });
}

auto thread_safe_list_test(size_t number) -> void {
   ankerl::nanobench::Bench().minEpochIterations(109).run("thread-safe-list", [=] {
      thread_safe_list_one_round(number);
   });
}

int main() {
   double_end_list_test(10);
   //lock_free_list_test(10);
   thread_safe_list_test(10);
}
