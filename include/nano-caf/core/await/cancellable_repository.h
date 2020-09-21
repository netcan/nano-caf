//
// Created by Darwin Yuan on 2020/9/21.
//

#ifndef NANO_CAF_CANCELLABLE_REPOSITORY_H
#define NANO_CAF_CANCELLABLE_REPOSITORY_H

#include <nano-caf/util/status_t.h>
#include <unordered_set>
#include <memory>
#include "cancellable.h"

NANO_CAF_NS_BEGIN

struct cancellable_repository {
   auto add_cancellable(std::shared_ptr<cancellable> object) noexcept -> void {
      objects_.insert(std::move(object));
   }

   auto remove_cancellable(std::shared_ptr<cancellable> const& object) noexcept -> void {
      objects_.erase(object);
   }

private:
   std::unordered_set<std::shared_ptr<cancellable>> objects_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_CANCELLABLE_REPOSITORY_H
