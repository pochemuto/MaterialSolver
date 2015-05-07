//
// Created by pochemuto on 07.05.15.
//

#include <assert.h>
#include <iostream>
#include "common.h"
#include "../struct/Polynomial.h"

int main() {

    TEST(10 + 7 * 7.2, Polynomial(10, 7).apply(7.2));
    TEST(3 + 6 * 7.2 + 8 * 7.2 * 7.2, Polynomial(3, 6, 8).apply(7.2));

    return 0;
}