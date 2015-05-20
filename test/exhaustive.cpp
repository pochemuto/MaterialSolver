//
// Created by pochemuto on 21.05.15.
//

#include <iostream>
#include <assert.h>
#include "common.h"
#include "../function/tpoint.h"
#include "../minimizer/ExhaustiveSearch.h"

int main() {
    TPoint center {10, -14};
    EllipticParaboloid f(center, 1, 1.5);
    f.scopeRadius = 120;

    TPoint start {-40, 90};
    ExhaustiveSearch<EllipticParaboloid> search(f, start, 1);

    TPoint point = search.search();
    TPoint expected {10, -14};
    ASSERT_ARRAY_EQUALS(expected.begin(), expected.end(), point.begin(), point.end());

}