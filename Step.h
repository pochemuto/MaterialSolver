//
// Created by pochemuto on 03.05.15.
//

#ifndef MATERIALSOLVER_STEP_H
#define MATERIALSOLVER_STEP_H

#include <vector>

using std::vector;

struct Step {
    const double f;
    const vector<double> x;

    Step(double const f, vector<double> const &x) : x(x), f(f) { }
};


#endif //MATERIALSOLVER_STEP_H
