//
// Created by pochemuto on 07.05.15.
//

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include "common.h"
#include "../struct/Polynomial.h"

int main() {

    ASSERT_EQAULS(10 + 7 * 7.2, Polynomial(10, 7).apply(7.2));
    ASSERT_EQAULS(3 + 6 * 7.2 + 8 * 7.2 * 7.2, Polynomial(3, 6, 8).apply(7.2));

    ASSERT_EQAULS(13.7 + 9.5 * 7.2, Polynomial(13.7, 9.5).maximize(-8.3, 7.2));
    ASSERT_EQAULS(-13.7 - 9.5 * (-8.3), Polynomial(-13.7, -9.5).maximize(-8.3, 7.2));

    ASSERT_EXCEPTION(Polynomial(1, 2, 3).maximize(10, 2), std::runtime_error);
    ASSERT_EXCEPTION(Polynomial(1, 2).maximize(10, -10), std::invalid_argument);

    return 0;
}