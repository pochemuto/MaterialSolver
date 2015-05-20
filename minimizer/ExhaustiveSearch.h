//
// Created by pochemuto on 04.05.15.
//

#ifndef MATERIALSOLVER_EXHAUSTIVESEARCH_H
#define MATERIALSOLVER_EXHAUSTIVESEARCH_H

#include <vector>
#include <float.h>
#include <assert.h>
#include <math.h>
#include <limits>
#include "../struct/Result.h"
#include "../function/tpoint.h"

using std::vector;

template <class Function>
class ExhaustiveSearch {
private:

    Function& func;
    double k;
    double f_min;
    const TPoint x_start;
    const unsigned int N; // количество переменных функции

    /*
     * bits - битовая маска, 0 - соответствует знаку минус, 1 - знаку плюс
     * возвращает множитель, соответствующий биту в pos
     */
    inline int signOf(unsigned long bits, int pos) {
        return ((bits >> pos) & 1) == 0 ? -1 : 1;
    }

public:

    ExhaustiveSearch(Function &function, const TPoint &x0, double k) :x_start(x0),k(k),func(function),
                                                                           N((unsigned int const) x0.size()){
        Result r = func.eval(x0);
        assert(r.success());
        f_min = r.value;
    }

    vector<double> search();

    static bool next(TPoint &point, const TPoint &shift, int fixedAxis, double min, double max, double step);

};

template <class Func>
bool ExhaustiveSearch<Func>::next(TPoint &point, const TPoint &shift,  int fixedAxis, double min, double max, double step) {
    int N = (int) point.size();
    for (int i = 0; i < N; ++i) {
        if (i == fixedAxis) {
            continue;
        }

        double nextVal = point[i] + step;
        if (nextVal > max + shift[i]) {
            point[i] = min + shift[i];

            // нужно увеличить следующий разряд, но мы уже на последнем
            // или последний - фиксирован, а мы на предпоследнем,
            // то считаем что перебрали все
            if (i == N - 1 || (i == N - 2 && fixedAxis == N - 1)) {
                return false;  // перебрали все
            }
        } else {
            point[i] = nextVal;
            // ещё влазит
            break;
        }
    }

    return true;
}

template <class Func>
TPoint ExhaustiveSearch<Func>::search() {
    TPoint arg(N);
    TPoint arg_max(N);
    double func_min = std::numeric_limits<double>::max();
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
            double endValue = x_start[axis] + r;
            for (double axisValue = x_start[axis] - r; axisValue <= endValue; axisValue += k) {
                arg[axis] = axisValue;
                Result r = func.eval(axisValue);
                if (!r.indeterminate()) {
                    hasPoint = true; // есть хотя бы одна точка на границе этого куба
                }
                if (r.success() && r.value < func_min) {
                    func_min = r.value;
                    arg_max = arg;
                }
            }
        }
    }

    /*
     * Обход всех N-1 мерных граней куба. При этом ребра уже пройдены на прошлом шаге
     * поэтому обходим только внутренние части, без границ -r и r
     */
    for (int axis = 0; axis < N; ++axis) {
        for (int i = 0; i < N; ++i) {
            arg[i] = x_start[i] - r + k;
        }
        do {
            for (int minus = 0; minus < 2; ++minus) {
                arg[axis] = (minus == 0) ? x_start[axis] - r : x_start[axis] + r;
            }
        } while (next(arg, x_start, axis, -r + k, r - k, k));
    }
}

#endif //MATERIALSOLVER_EXHAUSTIVESEARCH_H

