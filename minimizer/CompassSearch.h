//
// Created by pochemuto on 03.05.15.
//

#ifndef MATERIALSOLVER_COMPASSSEARCH_H
#define MATERIALSOLVER_COMPASSSEARCH_H

#include <vector>
#include <float.h>
#include <assert.h>
#include "../struct/Step.h"
#include "../struct/Result.h"

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


template<class Func>
vector<double> CompassSearch<Func>::search() {
    double delta = 0;
    do {
        Step step = doStep();
        if (step.f < f_star) {
            x_star = step.x;
            delta = step.f - f_star;
            f_star = step.f;
        } else {
            if (!shrinkK()) {
                // так сильно скукожили k, что вот прям некуда
                return x_star;
            }
        }
    } while (func.continueFind(f_star, delta));

    return x_star;
}

template<class Func>
Step CompassSearch<Func>::doStep() {
    point x_min;
    double f_min = DBL_MAX;
    bool foundOne = false; // нашли хотя-бы одно направление
    // по каждой координате идем в обе стороны
    for (int i = 0; i < N; ++i) {
        for (int dir = 0; dir < 2; ++dir) {
            vector<double> x_step = stepFor(i, dir == 0 ? DIR_FORWARD : DIR_BACKWARD);
            Result f_step = func.eval(x_step);
            if (f_step.success && f_step.value < f_min) {
                f_min = f_step.value;
                x_min = x_step;
                foundOne = true;
            }
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
typename CompassSearch<Func>::point CompassSearch<Func>::stepFor(int i, int direction) {
    point x_step = x_star;
    x_step[i] += k * direction;
    return x_step;
}


#endif //MATERIALSOLVER_COMPASSSEARCH_H
