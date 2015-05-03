//
// Created by pochemuto on 03.05.15.
//

#ifndef MATERIALSOLVER_RESULT_H
#define MATERIALSOLVER_RESULT_H

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

const Result Result::FALSE(DBL_MAX, false);

#endif //MATERIALSOLVER_RESULT_H
