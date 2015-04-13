//
// Created by pochemuto on 13.04.15.
//

#ifndef MATERIALSOLVER_POLYNOM_H
#define MATERIALSOLVER_POLYNOM_H

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
};

#endif //MATERIALSOLVER_POLYNOM_H
