//
// Created by pochemuto on 20.05.15.
//

#include <iostream>
#include <assert.h>
#include "common.h"
#include "../function/tpoint.h"
#include "../minimizer/CompassSearch.h"


int main() {
    TPoint center {10, -14};
    EllipticParaboloid f(center, 1, 1.5);
    f.scopeRadius = 1000;

    // просто проверим что функция задана верно
    ASSERT_EQAULS_EPS(17.77778, f.eval((TPoint) {6, -16}).value, 0.0001);
    ASSERT_EQAULS_EPS(0.0, f.eval(center).value, 0.0001);
    ASSERT_TRUE(f.eval((TPoint) {9000, 4000}).indeterminate());

    TPoint start {-100, 500};
    CompassSearch<EllipticParaboloid> search(f, start, 50);

    TPoint point = search.search();
    TPoint expected {10, -14};
    ASSERT_ARRAY_EQUALS(expected.begin(), expected.end(), point.begin(), point.end());

    return 0;
}
