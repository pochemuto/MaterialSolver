//
// Created by pochemuto on 13.04.15.
//

#ifndef MATERIALSOLVER_POLYNOM_H
#define MATERIALSOLVER_POLYNOM_H

#include <stdexcept>
#include <assert.h>

/*
 * Полином C1 + C2*y + C3*y^2
 */
struct Polynomial {
    double C1;
    double C2;
    double C3;

    Polynomial(double C1 = 0, double C2 = 0, double C3 = 0) : C1(C1), C2(C2), C3(C3) { }

    double apply(double y) {
        return C1 + C2 * y + C2 * y * y;
    }

    double maximize(double a, double b) {
        if (C3 != 0) {
            // там достаточно сложно - нам не нужно
            throw std::runtime_error("not implemented for C3 != 0");
        }
        if (a >= b) {
            throw std::invalid_argument("b lower or equal a. Must be a > b");
        }
        if (C2 < 0) {
            return apply(a);
        }
        if (C2 > 0) {
            return apply(b);
        }
        assert(C2 == 0);
        return apply(0); // не зависит от y
    }
};

#endif //MATERIALSOLVER_POLYNOM_H
