//
// Created by pochemuto on 07.05.15.
//

#include <iostream>
#include <assert.h>
#include "common.h"
#include "../minimizer/ExhaustiveSearch.h"
#include "../function/FixedThickness.h"

using namespace std;

struct Func {
    Result eval(vector<double> x) {
        return 0;
    }
};

typedef double point[4];

int testNext(ExhaustiveSearch<Func> &search, point combination, vector<double> &x) {
    ASSERT_TRUE(search.next(x, 1, 40, 42, 1));
    ASSERT_ARRAY_EQUALS(combination, combination + 4, x.begin(), x.end());

    return 0;
}

/*
 * Тестируем функция перебора
 */
int main() {
    Func f;
    vector<double> x0 {41, 72, 41, 41};
    ExhaustiveSearch<Func> search(f, x0, 0.1);

    TEST(testNext(search, (point) {42, 72, 41, 41}, x0));

    TEST(testNext(search, (point) {40, 72, 42, 41}, x0));
    TEST(testNext(search, (point) {41, 72, 42, 41}, x0));
    TEST(testNext(search, (point) {42, 72, 42, 41}, x0));

    TEST(testNext(search, (point) {40, 72, 40, 42}, x0));
    TEST(testNext(search, (point) {41, 72, 40, 42}, x0));
    TEST(testNext(search, (point) {42, 72, 40, 42}, x0));

    TEST(testNext(search, (point) {40, 72, 41, 42}, x0));
    TEST(testNext(search, (point) {41, 72, 41, 42}, x0));
    TEST(testNext(search, (point) {42, 72, 41, 42}, x0));

    TEST(testNext(search, (point) {40, 72, 42, 42}, x0));
    TEST(testNext(search, (point) {41, 72, 42, 42}, x0));
    TEST(testNext(search, (point) {42, 72, 42, 42}, x0));

    ASSERT_FALSE(search.next(x0, 1, 40, 42, 1));
}

