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
    double H;
    std::vector<Layer> layers;
    VectorXd Tcoeffs;

public:
    MaterialSolver(std::vector<Layer> layers, double t, double tN) : t(t), tN(tN) {
        this->layers = layers;
        H = 0;
        for (auto l : layers) {
            H += l.y;
        }
    }

    inline int getN() { return (int) layers.size(); }

    void start();

    double getT(double y);

    VectorXd solveT();

    MatrixXd createMatrixT();

    double segmT(double y, int n);
};


#endif //MATERIALSOLVER_MATERIALSOLVER_H
