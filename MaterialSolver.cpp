//
// Created by pochemuto on 29.03.15.
//

#include <iostream>
#include <assert.h>
#include <float.h>
#include "MaterialSolver.h"


using namespace std;

void MaterialSolver::start() {
    calculateH();
    Tcoeffs = solveT();
    Vcoeffs = solveV();
}

VectorXd MaterialSolver::solveT() {
    unsigned int N = getN();
    MatrixXd matT = createMatrixT();
    VectorXd right = VectorXd::Zero(2 * N);
    right(0) = t;
    right(2 * N - 1) = tN;
    return matT.colPivHouseholderQr().solve(right);
}

VectorXd MaterialSolver::solveV() {
    MatrixXd matV = createMatrixV();
    VectorXd right = createRightV();
    return matV.colPivHouseholderQr().solve(right);
}


MatrixXd MaterialSolver::createMatrixT() {
    unsigned int N = getN();
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
    double H = getH(); // здесь накопилась вся толщина слоя

    // нижняя половина (элементы k0 0 -k1), до предпоследней строчки
    column = 1;
    for (int i = 0; i < N - 1; ++i) {
        mat(N + i, column) = layers[i].k;
        mat(N + i, column + 2) = -layers[i + 1].k;
        column += 2;
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
    return getT(y, n);
}

double MaterialSolver::getT(double y, int n) {
    if (n < 0 || n >= getN()) {
        throw out_of_range("invalid layer number");
    }
    return C1(n) + C2(n) * y;
}

MatrixXd MaterialSolver::createMatrixV() {
    unsigned int N = getN();
    int e_column = 2 * N;
    MatrixXd mat = MatrixXd::Zero(N * 2 + 1, N * 2 + 1);
    double M_left = M(0), M_right = M_left;
    // строчки вида (0 M0 0 -M1)
    mat(0, 1) = M_right;
    mat(0, e_column) = 2 * layers[0].l;
    for (int i = 1; i < N; ++i) {
        M_right = -M(i);
        mat(i, 2 * i - 1) = M_left;
        mat(i, 2 * i + 1) = M_right;
        mat(i, e_column) = 2 * (layers[i - 1].l - layers[i].l);
        M_left = -M_right;
    }

    // строчки вида (1 y0 -1 -y1)
    int row = N;
    double y = 0;
    for (int i = 0; i < N - 1; ++i) {
        y += layers[i].y;
        mat(row, 2 * i) = 1;
        mat(row, 2 * i + 1) = y;
        mat(row, 2 * i + 2) = -1;
        mat(row, 2 * i + 3) = -y;
        row++;
    }
    mat(row, 2 * (N - 1)) = 1;
    mat(row, 2 * (N - 1) + 1) = getH();
    row++;

    assert(row == 2 * N);
    double e_coeff = 0;
    // последняя строчка
    for (int i = 0; i < N; ++i) {
        mat(row, 2 * i + 1) = layers[i].l * layers[i].y;
        e_coeff += (layers[i].l + layers[i].mu) * layers[i].y;
    }
    mat(row, e_column) = 2 * e_coeff;

    return mat;
}

VectorXd MaterialSolver::createRightV() {
    unsigned int N = getN();
    VectorXd vec(2*N + 1);
    double H = getH();
    vec(0) = -P(0, 0);

    double y = 0;
    double v_right = V(0), v_left;
    for (int i = 0; i < N - 1; ++i) {
        y += layers[i].y;
        vec(i + 1) = P(i + 1, y) - P(i, y);

        v_left = V(i + 1);
        vec(N + i) = (v_left - v_right) * y * y;
        v_right = v_left;
    }

    vec(2 * N - 1) = -V(N - 1) * H * H;

    double t = 0;
    for (int i = 0; i < N; ++i) {
        t += T(i);
    }
    vec(2 * N) = t;
    return vec;
}

vector<Polynomial> MaterialSolver::functionT() {
    unsigned int N = getN();
    vector<Polynomial> result(N);
    for (int i = 0; i < N; ++i) {
        result[i] = Polynomial(C1(i), C2(i));
    }
    return result;
}

vector<Polynomial> MaterialSolver::functionV() {
    unsigned int N = getN();
    vector<Polynomial> result(N);
    for (int i = 0; i < N; ++i) {
        result[i] = Polynomial(D1(i), D2(i), D3(i));
    }
    return result;
}

vector<Polynomial> MaterialSolver::functionSigmaX() {
    unsigned int N = getN();
    vector<Polynomial> result(N);
    for (int i = 0; i < N; ++i) {
        Layer &L = layers[i];
        double c1 = 2 * (L.mu + L.l) * ex() + L.l * D2(i) - 3 * L.K * L.a * C1(i);
        double c2 = 2 * L.l * V(i) - 3 * L.K * L.a * C2(i);
        result[i] = Polynomial(c1, c2);
    }
    return result;
}

void MaterialSolver::calculateH() {
    H = 0;
    for (auto l : layers) {
        H += l.y;
    }
}

double MaterialSolver::sigmaXMax() {
    vector<Polynomial> sigmaX = functionSigmaX();
    double y_from = 0;
    double sigma_max = 0;
    for (int i = 0; i < sigmaX.size(); ++i) {
        double y_to = y_from + layers[i].y;
        double segment_max = abs(sigmaX[i].maximize(y_from, y_to));
        if (abs(segment_max) > sigma_max) {
            sigma_max = segment_max;
        }
        y_from = y_to;
    }
    return sigma_max;
}
