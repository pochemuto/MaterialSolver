//
// Created by pochemuto on 29.03.15.
//

#ifndef MATERIALSOLVER_MATERIALSOLVER_H
#define MATERIALSOLVER_MATERIALSOLVER_H


#include "Eigen/Dense"

using namespace Eigen;

class MaterialSolver {
private:
    const int         N; // количество слоев
    const double*     y;      // толщины слоев
    const double*     k;      // коэффициенты теплопроводности
    const double      t;      // температура над материалом
    const double      tN;     // температура под материалом

public:
    MaterialSolver(int const layers, double const *y, double const *k, double const t, double const tN) : N(layers),
                                                                                                          y(y), k(k), t(t),
                                                                                                          tN(tN) { }

    void start();

    VectorXd solveT();

    MatrixXd createMatrixT();
};


#endif //MATERIALSOLVER_MATERIALSOLVER_H
