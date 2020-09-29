//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_FUTURE_REPOSITORY_H
#define NANO_CAF_FUTURE_REPOSITORY_H

#include <nano-caf/core/await/abstract_future.h>
#include <unordered_set>
#include <memory>

NANO_CAF_NS_BEGIN

struct future_repository {
   using elem_type = std::shared_ptr<abstract_future>;

   auto add_future(elem_type object) noexcept -> void {
      objects_.insert(std::move(object));
   }

   auto remove_future(abstract_future* object) noexcept -> void {
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
   std::unordered_set<elem_type> objects_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_FUTURE_REPOSITORY_H
