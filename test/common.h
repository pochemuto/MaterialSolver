//
// Created by pochemuto on 07.05.15.
//

#ifndef MATERIALSOLVER_COMMON_H
#define MATERIALSOLVER_COMMON_H

#include <iostream>
#include <string>

#define STR(s) #s

#define TEST_BOOL(expr) if (!expr) return -1
#define TEST(expr) if (expr != 0) return -1

#define ASSERT_EQAULS(expected, actual) TEST_BOOL(testing::assert_equals(expected, actual, STR(actual)))

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

#endif //MATERIALSOLVER_COMMON_H
