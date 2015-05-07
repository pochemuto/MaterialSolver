//
// Created by pochemuto on 04.05.15.
//

#ifndef MATERIALSOLVER_EXHAUSTIVESEARCH_H
#define MATERIALSOLVER_EXHAUSTIVESEARCH_H

#include <vector>
#include <float.h>
#include <assert.h>
#include <math.h>
#include "../struct/Result.h"

using std::vector;

template <class Function>
class ExhaustiveSearch {
private:
    typedef vector<double> point;

    Function& func;
    double k;
    double f_star;
    point x_star;
    const unsigned int N; // количество переменных функции

    /*
     * bits - битовая маска, 0 - соответствует знаку минус, 1 - знаку плюс
     * возвращает множитель, соответствующий биту в pos
     */
    inline int signOf(unsigned long bits, int pos) {
        return (bits >> pos) & 1 == 0 ? -1 : 1;
    }

public:
    ExhaustiveSearch(Function &function, const vector<double> &x0, double k) :x_star(x0),k(k),func(function),
                                                                           N((unsigned int const) x0.size()){
        Result r = func.eval(x0);
        assert(r.success());
        f_star = r.value;
    }

    vector<double> search();
};

vector<double> ExhaustiveSearch::search() {
    vector<double> arg(N);
    vector<double> arg_max(N);
    double func_max = -DBL_MAX;
    double r = k;
    bool hasPoint = false;

    /*
     * Обход всех ребер N-мерного параллелограмма, с длиной ребра r
     * пробегаем по всем осям, и для каждой оси проходим по всем ребрам, параллельным этой оси
     */
    unsigned long signsMax = (unsigned long) pow(2, N + 1);
    for (int axis = 0; axis < N; ++axis) {
        /*
         * Перебираем все вершины N-мерного параллелограмма в плоскости axis = const
         * при этом проходим по ребру от этой вершины в направлении axis
         */
        for (unsigned long signs = 0; signs < signsMax; ++signs) { // знаки переменных - битовое значение
            // количество знаков на одно меньше, чем количество переменных
            // по одной переменной мы пробегаемся по всему интервалу
            // соответственно начиная с axis-элемента i будет отставать на единицу
            short int shift = 0;
            for (int i = 0; i < signsMax; ++i) {
                if (i == axis) {
                    shift = 1;
                }
                arg[i + shift] = signOf(signs, i) * r;
            }

            // на этом шаге у нас уже есть зафиксированная вершина
            for (double axisValue = -r; axisValue <= r; axisValue += k) {
                arg[axis] = axisValue;
                Result r = func.eval(axisValue);
                if (!r.indeterminate()) {
                    hasPoint = true; // есть хотя бы одна точка на границе этого куба
                }
                if (r.success() && r.value > func_max) {
                    func_max = r.value;
                    arg_max = arg;
                }
            }
        }
    }
}

#endif //MATERIALSOLVER_EXHAUSTIVESEARCH_H

