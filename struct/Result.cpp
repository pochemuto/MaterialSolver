//
// Created by pochemuto on 04.05.15.
//

#include "Result.h"

const Result Result::FALSE(DBL_MAX, false);

ostream &operator<<(ostream &os, const Result &r) {
    if (!r.success) {
        os << "Result::FALSE";
    } else {
        os << "Result[" << r.value << "]";
    }
    return os;
}
