//
// Created by Darwin Yuan on 2020/9/19.
//

#ifndef NANO_CAF_RANDOM_GENERATOR_H
#define NANO_CAF_RANDOM_GENERATOR_H

#include <nano-caf/nano-caf-ns.h>
#include <random>

NANO_CAF_NS_BEGIN

struct random_generator {
   random_generator(std::size_t l, std::size_t u)
      : uniform_(l, u) {}

   auto gen() -> std::size_t {
      return uniform_(regen_);
   }
private:
   std::random_device r_;
   std::default_random_engine regen_{r_()};
   std::uniform_int_distribution<size_t> uniform_;
};

NANO_CAF_NS_END

#endif //NANO_CAF_RANDOM_GENERATOR_H
