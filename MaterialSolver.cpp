//
// Created by pochemuto on 29.03.15.
//

#include <iostream>
#include <stdexcept>
#include "MaterialSolver.h"


using namespace std;

void MaterialSolver::start() {
    Tcoeffs = solveT();
}

VectorXd MaterialSolver::solveT() {
    int N = getN();
    MatrixXd matT = createMatrixT();
    VectorXd left = VectorXd::Zero(2*N);
    left(0) = t;
    left(2*N - 1) = tN;
    return matT.colPivHouseholderQr().solve(left);
}

MatrixXd MaterialSolver::createMatrixT() {
    int N = getN();
    MatrixXd mat = MatrixXd::Zero(N * 2, N * 2);
    mat(0, 0) = 1;
    // верхняя половина (элементы y -1 y), начиная со второй строчки
    double y = 0;
    int column = 0;
    for (int i = 1; i < N; ++i) {
        y += layers[i - 1].y;
        mat(i, column) = 1;
        mat(i, column + 1) = y;
        mat(i, column + 2) = -1;
        mat(i, column + 3) = -y;
        column += 2;
    }
    double H = y + layers[N - 1].y; // здесь накопилась вся толщина слоя

    // нижняя половина (элементы k0 0 -k1), до предпоследней строчки
    column = 1;
    for (int i = 0; i < N - 1; ++i) {
        mat(N + i, column) = layers[i].k;
        mat(N + i, column + 2) = -layers[i + 1].k;
    }
    mat(2 * N - 1, 2 * N - 2) = 1;
    mat(2 * N - 1, 2 * N - 1) = H;
    return mat;
}

double MaterialSolver::getT(double y) {
    if (y < 0 || y > H) {
        throw out_of_range("y must be in range [0,H]");
    }
    int n = 0;
    double lower = 0, upper = 0;
    for (auto l : layers) {
        upper += l.y;
        if (y >= lower && y <= upper) {
            break;
        }
        lower = upper;
        n++;
    }
    cout << "n = " << n << endl;
    return getT(y, n);
}

double MaterialSolver::getT(double y, int n) {
    if (n < 0 || n >= getN()) {
        throw out_of_range("invalid layer number");
    }
    return C1(n) + C2(n) * y;
}
