//
// Created by pochemuto on 03.05.15.
//

#include <float.h>
#include <assert.h>
#include "CompassSearch.h"

template<class Func>
vector<double> CompassSearch<Func>::search() {
    Step step = doStep();
    if (step.f < f_star) {
        x_star = step.x;
    } else {
        if (!shrinkK()) {
            // так сильно скукожили k, что вот прям некуда
            return x_star;
        }
    }

    return x_star;
}

template<class Func>
Step CompassSearch<Func>::doStep() {
    point x_min;
    double f_min = -DBL_MAX;
    bool foundOne = false; // нашли хотя-бы одно направление
    for (int i = 0; i < N; ++i) {
        vector<double> x_step = stepFor(i);
        Result f_step = func.eval(x_step);
        if (f_step.success && f_step.value < f_min) {
            f_min = f_step.value;
            x_min = x_step;
            foundOne = true;
        }
    }
    assert(foundOne); // по идее, в худшем случае мы вернемся к предыдущей точке
    Step result(f_min, x_min);
    return result;
}

template<class Func>
bool CompassSearch<Func>::shrinkK() {
    double prevK = k;
    k *= 0.80;
    return prevK != k;
}

template<class Func>
typename CompassSearch<Func>::point CompassSearch<Func>::stepFor(int i) {
    point x_step = x_star;
    x_step[i] += k;
    return x_step;
}
