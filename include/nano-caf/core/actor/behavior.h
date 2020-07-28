//
// Created by Darwin Yuan on 2020/7/28.
//

#ifndef NANO_CAF_BEHAVIOR_H
#define NANO_CAF_BEHAVIOR_H

#include <nano-caf/nano-caf-ns.h>
#include <tuple>
#include <nano-caf/util/type_list.h>
#include <nano-caf/util/callable_trait.h>

NANO_CAF_NS_BEGIN

struct behavior {
   template<typename ... Args>
   behavior(Args&&...args) {
      static_assert(((callable_trait<Args>::num_of_args > 0) && ...));
      static_assert(((callable_trait<Args>::num_of_args > 0) && ...));
      using types = type_list<callable_trait<Args>...>;
      using first_arg = type_list<callable_trait<Args>...>;
      //std::tuple<std::decay_t<Args>...>{std::forward<Args>(args)...};
   }
};

NANO_CAF_NS_END

#endif //NANO_CAF_BEHAVIOR_H
