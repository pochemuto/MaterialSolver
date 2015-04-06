//
// Created by pochemuto on 29.03.15.
//

#ifndef MATERIALSOLVER_MATERIALSOLVER_H
#define MATERIALSOLVER_MATERIALSOLVER_H


#include "Eigen/Dense"
#include "Material.h"
#include <vector>

using namespace Eigen;

class MaterialSolver {
private:
    double t;
    double tN;
    std::vector<Layer> layers;

public:
    MaterialSolver(std::vector<Layer> layers, double t, double tN) : t(t), tN(tN) {
        this->layers = layers;
    }

    inline int getN() { return (int) layers.size(); }

    void start();

    VectorXd solveT();

    MatrixXd createMatrixT();
};


#endif //MATERIALSOLVER_MATERIALSOLVER_H
