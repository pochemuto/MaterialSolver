//
// Created by pochemuto on 04.05.15.
//

#include "Result.h"

const Result Result::INDETERMINATE(TYPE_INDETERMINATE);
const Result Result::VIOLATED(TYPE_VIOLATED);

ostream &operator<<(ostream &os, const Result &r) {
    switch (r.type) {
        case Result::TYPE_SUCCESS:
            os << "Result[" << r.value << "]";
            break;
        case Result::TYPE_INDETERMINATE:
            os << "Result::INDETERMINATE";
            break;
        case Result::TYPE_VIOLATED:
            os << "Result::TYPE_VIOLATED";
            break;
    }
    return os;
}
