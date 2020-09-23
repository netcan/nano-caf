//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_AWAITER_REPOSITORY_H
#define NANO_CAF_AWAITER_REPOSITORY_H

#include <nano-caf/util/status_t.h>
#include <nano-caf/core/await/awaiter.h>
#include <unordered_set>
#include <memory>

NANO_CAF_NS_BEGIN

struct awaiter_repository {
   auto add_cancellable(std::shared_ptr<awaiter> object) noexcept -> void {
      objects_.insert(std::move(object));
   }

   auto remove_cancellable(awaiter* object) noexcept -> void {
      for(auto&& obj : objects_) {
         if(obj.get() == object) {
            objects_.erase(obj);
            return;
         }
      }
   }

   auto empty() const noexcept -> bool {
      return objects_.empty();
   }

private:
   std::unordered_set<std::shared_ptr<awaiter>> objects_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_AWAITER_REPOSITORY_H
