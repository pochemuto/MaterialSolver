//
// Created by pochemuto on 03.05.15.
//

#ifndef MATERIALSOLVER_COMPASSSEARCH_H
#define MATERIALSOLVER_COMPASSSEARCH_H

#include <vector>
#include "Step.h"
#include "Result.h"

using std::vector;

template <class Function>
class CompassSearch {
private:
    typedef vector<double> point;

    Function& func;
    double k;
    double f_star;
    point x_star;
    const unsigned long N;


    point stepFor(int i);
    bool shrinkK();
    Step doStep();

public:
    CompassSearch(const vector<double>& x0, double k, Function& function):x_star(x0),k(k),func(function),N(x0.size()){
        f_star = func.eval(x0);
    }

    vector<double> search();
};

#endif //MATERIALSOLVER_COMPASSSEARCH_H
