//
// Created by pochemuto on 07.05.15.
//

#ifndef MATERIALSOLVER_COMMON_H
#define MATERIALSOLVER_COMMON_H

#include <iostream>

#define STR(s) #s

#define TEST(expected, actual) { \
    auto __actual = actual; \
    auto __expected = expected; \
    if (__actual != __expected) { \
        std::cerr << ">>> ERROR: " << STR(actual) << "; expected = '" << __expected << "'; actual = '" << __actual << "'" << std::endl; \
        return 1; \
    } \
}

#define IS_TRUE(actual)  TEST(true, actual)
#define IS_FALSE(actual) TEST(false, actual)

#endif //MATERIALSOLVER_COMMON_H
