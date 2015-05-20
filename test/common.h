//
// Created by pochemuto on 07.05.15.
//

#ifndef MATERIALSOLVER_COMMON_H
#define MATERIALSOLVER_COMMON_H

#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>
#include "../function/tpoint.h"
#include "../struct/Result.h"

#define STR(s) #s

#define TEST_BOOL(expr) if (!expr) return -1
#define TEST(expr) if (expr != 0) return -1

#define ASSERT_EQAULS(expected, actual) TEST_BOOL(testing::assert_equals(expected, actual, STR(actual)))
#define ASSERT_EQAULS_EPS(expected, actual, eps) TEST_BOOL(testing::assert_equals(expected, actual, eps, STR(actual)))

#define ASSERT_TRUE(actual)  TEST_BOOL(testing::assert_true(actual, STR(actual)))
#define ASSERT_FALSE(actual) TEST_BOOL(testing::assert_false(actual, STR(actual)))

#define ASSERT_ARRAY_EQUALS(expected_begin, expected_end, actual_begin, actual_end) TEST_BOOL(testing::assert_array_equals(expected_begin, expected_end, actual_begin, actual_end, STR(actual_begin)))

#define ASSERT_EXCEPTION(expr, exception) try {\
        expr; \
        std::cerr << ">>> ERROR: " << STR(expr) << "; expected exception " << STR(exception) << " not thrown" << std::endl;\
        return -1; \
    } catch (exception e) {}

namespace testing {
    using std::string;
    using std::cerr;
    using std::endl;

    template<typename T>
    bool assert_equals(T expected, T actual, string expression) {
        if (expected != actual) { \
            cerr << ">>> ERROR: " << expression << "; expected = '" << expected << "'; actual = '" << actual << "'" << endl;
            return false;
        } else {
            return true;
        }
    }

    template<typename T>
    bool assert_equals(T expected, T actual, T eps, string expression) {
        if (expected > actual + eps || expected < actual - eps) { \
            cerr << ">>> ERROR: " << expression << "; expected = '" << expected << "'; actual = '" << actual << "'" << endl;
            return false;
        } else {
            return true;
        }
    }

    template<typename T>
    bool assert_true(T actual, string expression) {
        if (!actual) { \
            cerr << ">>> ERROR: " << expression << "; expected = true; actual = '" << actual << "'" << endl;
            return false;
        } else {
            return true;
        }
    }

    template<typename T>
    bool assert_false(T actual, string expression) {
        if (actual) { \
            cerr << ">>> ERROR: " << expression << "; expected = false; actual = '" << actual << "'" << endl;
            return false;
        } else {
            return true;
        }
    }

    template<typename T1, typename T2>
    bool assert_array_equals(T1 expected_begin, T1 expected_end, T2 actual_begin, T2 actual_end, string expression) {
        auto expected_length = expected_end - expected_begin;
        auto actual_length = actual_end - actual_begin;
        if (actual_length != expected_length) {
            cerr << ">>> ERROR: " << expression << " length missmatch; expected = '" << expected_length << "'; actual = '" << actual_length << "'" << endl;
            return false;
        }
        while (actual_length--) {
            if (*expected_begin != *actual_begin) {
                cerr << ">>> ERROR: " << expression << " at position " << (expected_length - actual_length - 1) << "; expected = '" << *expected_begin << "'; actual = '" << *actual_begin << "'" << endl;
                return false;
            }
            expected_begin++;
            actual_begin++;
        }

        return true;
    }
}

#define _TRACE_FUNCTION_CALL

class EllipticParaboloid {
    const TPoint center;
    const double a2;
    const double b2;

    inline double sqr(double val) {
        return val*val;
    }

public:
    double scopeRadius = 0;

    EllipticParaboloid(TPoint const &center, double a = 1, double b = 1) : center(center),a2(a*a),b2(b*b) {
        assert(a != 0);
        assert(b != 0);
        assert(center.size() == 2);
    }

    Result eval(TPoint x) {
        #ifdef TRACE_FUNCTION_CALL
        std::cout << "func(" << x[0] << ", " << x[1] << ") = ";
        #endif
        if (scopeRadius > 0 && sqrt(sqr(x[0] - center[0]) + sqr(x[1] - center[1])) > scopeRadius) {
            // вышли за область определения
            #ifdef TRACE_FUNCTION_CALL
            std::cout << "indeterminate" << std::endl;
            #endif
            return Result::INDETERMINATE;
        }
        double value = sqr(x[0] - center[0])/a2 + sqr(x[1] - center[1])/b2;
        #ifdef TRACE_FUNCTION_CALL
        std::cout << value << std::endl;
        #endif
        return value;
    }
};

#endif //MATERIALSOLVER_COMMON_H
