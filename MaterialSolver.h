//
// Created by pochemuto on 29.03.15.
//

#ifndef MATERIALSOLVER_MATERIALSOLVER_H
#define MATERIALSOLVER_MATERIALSOLVER_H


#include <vector>
#include "Eigen/Dense"
#include "Material.h"
#include "Polynomial.h"

using namespace std;
using namespace Eigen;

class MaterialSolver {
private:
    double t;
    double tN;
    double H;
    vector<Layer> layers;
    VectorXd Tcoeffs;
    VectorXd Vcoeffs;

    inline double C1(int i) {
        return Tcoeffs(2 * i);
    }

    inline double C2(int i) {
        return Tcoeffs(2 * i + 1);
    }

    inline double D1(int i) {
        return Vcoeffs(2 * i);
    }

    inline double D2(int i) {
        return Vcoeffs(2 * i + 1);
    }

    inline double D3(int i) {
        return V(i);
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
        Layer &L = layers[i];
        h = h * 2 + L.y;
        return 3 * L.K * L.a * C1(i) * L.y
               + (1.5 * L.K * L.a * C2(i) - L.l * V(i)) * L.y * h;
    }

    double getT(double y);

    double getT(double y, int n);


    VectorXd solveT();

    MatrixXd createMatrixT();

    MatrixXd createMatrixV();

    VectorXd createRightV();

    VectorXd solveV();

    void calculateH();

public:
    MaterialSolver(vector<Layer> layers, double t, double tN) : t(t), tN(tN) {
        this->layers = layers;
        calculateH();
    }

    inline unsigned int getN() { return (uint) layers.size(); }

    inline double getH() { return H; }

    inline double ex() {
        return Vcoeffs(2 * getN()); // последнее значение в векторе
    }

    void start();

    vector<Polynomial> functionT();

    vector<Polynomial> functionV();

    vector<Polynomial> functionSigmaX();

    inline Layer& layer(int n) {
        return layers[n];
    }
};


#endif //MATERIALSOLVER_MATERIALSOLVER_H
