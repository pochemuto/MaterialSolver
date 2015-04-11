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
    VectorXd Vcoeffs;

public:
    MaterialSolver(std::vector<Layer> layers, double t, double tN) : t(t), tN(tN) {
        this->layers = layers;
        H = 0;
        for (auto l : layers) {
            H += l.y;
        }
    }

    inline int getN() { return (int) layers.size(); }

    inline double getH() { return H; }

    inline double C1(int i) {
        return Tcoeffs(2 * i);
    }

    inline double C2(int i) {
        return Tcoeffs(2 * i + 1);
    }

    inline double V(int i) {
        return 3 * layers[i].a * C2(i) * layers[i].K / 2 / (layers[i].l + 2 * layers[i].mu);
    }

    inline double M(int i) {
        return 2 * layers[i].mu + layers[i].l;
    }

    inline double P(int i, double y) {
        return 2 * (2 * layers[i].mu + layers[i].l) * V(i) * y - 3 * layers[i].K * layers[i].a * getT(y, i);
    }

    inline double T(int i) {
        // (y_i^2 - y_{i-1}^2) = (y_i - y_{i-1})(y_i + y_{i-1})
        //                       |-------------||-------------|
        //                       толщина слоя i      h
        int N = getN();
        double h = 0;
        for (int j = 0; j < i; ++j) {
            h += layers[j].y;
        }
        h = h * 2 + layers[i].y;
        return 3*layers[i].K*layers[i].a*layers[i].y
               + (1.5 * layers[i].K * layers[i].a * C2(i) - layers[i].l * V(i)) * h;
    }


    void start();

    double getT(double y);

    VectorXd solveT();

    MatrixXd createMatrixT();

    MatrixXd createMatrixV();

    VectorXd createRightV();

    double getT(double y, int n);

    VectorXd solveV();
};


#endif //MATERIALSOLVER_MATERIALSOLVER_H
