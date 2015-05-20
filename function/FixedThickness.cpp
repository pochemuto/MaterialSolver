//
// Created by pochemuto on 04.05.15.
//

#include <iostream>
#include "FixedThickness.h"

Result FixedThickness::eval(TPoint point) {
    if (!applyPoint(point)) {
        return Result::INDETERMINATE;
    }

    solver->start();
    return solver->sigmaXMax();
}

bool FixedThickness::applyPoint(const TPoint &point) {
    unsigned int pointSize = (unsigned int) x0_.size();
    assert(point.size() == pointSize);
    double y_last = 0;
    TPoint heights(pointSize);
    for (int i = 0; i < pointSize; ++i) {
        double y = point[i];
        double h = y - y_last;
        if (h <= 0) {
            return false; // один из слоев сложился в ноль
        }
        heights[i] = h;
        y_last = y;
    }

    double lastHeight = thick - y_last; // толщина последнего слоя зависит
    if (lastHeight <= 0) {
        return false; // последний слой сложился в ноль
    }

    for (int i = 0; i < pointSize; ++i) {
        solver->layer(i).y = heights[i];
    }
    solver->layer(pointSize).y = lastHeight;

    for (int i = 0; i < pointSize + 2; ++i) {
        std::cout << i << " = " << solver->layer(i).y << std::endl;
    }
    return true;
}
