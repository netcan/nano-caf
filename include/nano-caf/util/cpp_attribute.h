//
// Created by godsme on 8/11/20.
//

#ifndef NANO_CAF_CPP_ATTRIBUTE_H
#define NANO_CAF_CPP_ATTRIBUTE_H

#ifdef __clang__
#define __MAYBE_UNUSED__ [[maybe_unused]]
#elif defined(__GNUG__) && !defined(__clang__)
#define __MAYBE_UNUSED__
#endif

#endif //NANO_CAF_CPP_ATTRIBUTE_H
