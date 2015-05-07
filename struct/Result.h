//
// Created by pochemuto on 03.05.15.
//

#ifndef MATERIALSOLVER_RESULT_H
#define MATERIALSOLVER_RESULT_H

#include <float.h>
#include <iostream>

using std::ostream;

/*
 * Инкапсулирует значение функции или сигнал, что значение не должно быть использовано.
 */
class Result {

    enum TYPE {
        TYPE_SUCCESS,        // успешный результат
        TYPE_INDETERMINATE,  // функция в заданной точке не определена
        TYPE_VIOLATED        // нарушены ограничения
    };

    const TYPE type;

public:
    const double value;

    Result(double value): type(TYPE_SUCCESS),value(value){}

    // статическое значение - отсутствие результата
    static const Result INDETERMINATE;
    static const Result VIOLATED;

    inline bool indeterminate() {
        return type == TYPE_INDETERMINATE;
    }

    inline bool violated() {
        return type == TYPE_VIOLATED;
    }

    inline bool success() {
        return type == TYPE_SUCCESS;
    }

    friend ostream& operator<<(ostream& os, const Result& r);


private:
    Result(Result::TYPE type): type(type),value(-DBL_MAX){}
};

#endif //MATERIALSOLVER_RESULT_H
