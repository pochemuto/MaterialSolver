//
// Created by pochemuto on 07.05.15.
//

#include <iostream>
#include "common.h"
#include "../function/tpoint.h"
#include "../minimizer/ExhaustiveSearch.h"
#include "../function/FixedThickness.h"

using namespace std;

struct Func {
    Result eval(vector<double> x) {
        return 0;
    }
};

typedef double point[4];

int testNext(ExhaustiveSearch<Func> &search, const TPoint &shift, point expected, TPoint &x) {
    ASSERT_TRUE(search.next(x, shift, 1, 40, 42, 1));
    ASSERT_ARRAY_EQUALS(expected, expected + 4, x.begin(), x.end());

    return 0;
}

int testZeroShift() {
    Func f;
    TPoint zero {0, 0, 0, 0};

    TPoint x0 {41, 72, 41, 41};

    ExhaustiveSearch<Func> search(f, x0, 0.1);

    //testNext - интервал от 40 - 42
    TEST(testNext(search, zero, (point) {42, 72, 41, 41}, x0));

    TEST(testNext(search, zero, (point) {40, 72, 42, 41}, x0));
    TEST(testNext(search, zero, (point) {41, 72, 42, 41}, x0));
    TEST(testNext(search, zero, (point) {42, 72, 42, 41}, x0));

    TEST(testNext(search, zero, (point) {40, 72, 40, 42}, x0));
    TEST(testNext(search, zero, (point) {41, 72, 40, 42}, x0));
    TEST(testNext(search, zero, (point) {42, 72, 40, 42}, x0));

    TEST(testNext(search, zero, (point) {40, 72, 41, 42}, x0));
    TEST(testNext(search, zero, (point) {41, 72, 41, 42}, x0));
    TEST(testNext(search, zero, (point) {42, 72, 41, 42}, x0));

    TEST(testNext(search, zero, (point) {40, 72, 42, 42}, x0));
    TEST(testNext(search, zero, (point) {41, 72, 42, 42}, x0));
    TEST(testNext(search, zero, (point) {42, 72, 42, 42}, x0));

    ASSERT_FALSE(search.next(x0, zero, 1, 40, 42, 1));

    return 0;
}

int testShift() {
    Func f;
    TPoint shift{100, 200, 300, 900};

    TPoint x0 {141, 72, 341, 941};

    ExhaustiveSearch<Func> search(f, x0, 0.1);

    //testNext - интервал от 40 - 42

    TEST(testNext(search, shift, (point) {142, 72, 341, 941}, x0));

    TEST(testNext(search, shift, (point) {140, 72, 342, 941}, x0));
    TEST(testNext(search, shift, (point) {141, 72, 342, 941}, x0));
    TEST(testNext(search, shift, (point) {142, 72, 342, 941}, x0));

    TEST(testNext(search, shift, (point) {140, 72, 340, 942}, x0));
    TEST(testNext(search, shift, (point) {141, 72, 340, 942}, x0));
    TEST(testNext(search, shift, (point) {142, 72, 340, 942}, x0));

    TEST(testNext(search, shift, (point) {140, 72, 341, 942}, x0));
    TEST(testNext(search, shift, (point) {141, 72, 341, 942}, x0));
    TEST(testNext(search, shift, (point) {142, 72, 341, 942}, x0));

    TEST(testNext(search, shift, (point) {140, 72, 342, 942}, x0));
    TEST(testNext(search, shift, (point) {141, 72, 342, 942}, x0));
    TEST(testNext(search, shift, (point) {142, 72, 342, 942}, x0));

    ASSERT_FALSE(search.next(x0, shift, 1, 40, 42, 1));

    return 0;
}

/*
 * Тестируем функция перебора, x0 - фиксирована
 */
int main() {
    TEST(testZeroShift());
    TEST(testShift());

    return 0;
}

