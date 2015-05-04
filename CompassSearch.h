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
    const unsigned int N;


    // шаг по координате i в направлении DIR
    point stepFor(int i, int direction);
    bool shrinkK();
    Step doStep();

    static const int DIR_FORWARD = 1;
    static const int DIR_BACKWARD = -1;
public:
    CompassSearch(Function &function, const vector<double> &x0, double k) :x_star(x0),k(k),func(function),
                                                                           N((unsigned int const) x0.size()){
        Result r = func.eval(x0);
        assert(r.success);
        f_star = r.value;
    }

    vector<double> search();
};

#endif //MATERIALSOLVER_COMPASSSEARCH_H
