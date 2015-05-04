//
// Created by pochemuto on 03.05.15.
//

#ifndef MATERIALSOLVER_RESULT_H
#define MATERIALSOLVER_RESULT_H

#include <float.h>

/*
 * Инкапсулирует значение функции или сигнал, что значение не должно быть использовано.
 */
struct Result {
    const double value;
    const bool success;

    Result(double value): success(true),value(value){}

    // статическое значение - отсутствие результата
    static const Result FALSE;

private:
    Result(double value, bool success): success(success),value(value){}
};

#endif //MATERIALSOLVER_RESULT_H
