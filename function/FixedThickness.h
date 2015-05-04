//
// Created by pochemuto on 04.05.15.
//

#ifndef MATERIALSOLVER_FIXEDTHICKNESS_H
#define MATERIALSOLVER_FIXEDTHICKNESS_H


#include <vector>
#include <iostream>
#include "../struct/Result.h"
#include "../MaterialSolver.h"

using std::vector;
using std::cout;
using std::endl;

class FixedThickness {

    MaterialSolver* solver;
    vector<double> x0_;
    double thick;

    static const bool ceramicFirst = true;


public:
    bool applyPoint(const vector<double> &point);

    /*
     * bottom - слой подложка
     * layersCount - количество слоев, без подложки
     * thick - толщина слоев, без полдожки
     */
    explicit FixedThickness(Material &metal, Material &ceramic, Layer &bottom, double t, double tN, unsigned int layersCount, double thick):
            x0_(layersCount - 1) {
        double y = 0;
        this->thick = thick;
        double h = thick / layersCount; // толщина одного слоя
        vector<Layer> layers;
        bool ceramicNow = (layersCount % 2 == 1) == ceramicFirst;

        for (int i = 0; i < layersCount; ++i) {
            if (ceramicNow) {
                layers.push_back(Layer(ceramic, h));
            } else {
                layers.push_back(Layer(metal, h));
            }
            y += h;
            if (i < layersCount - 1) {
                // толщина последнего слоя зависит от предыдущих
                // т.к. толщина материала фиксирована
                x0_[i] = y;
            }
        }

        layers.push_back(bottom);
        assert(layers.size() == layersCount + 1);

        solver = new MaterialSolver(layers, t, tN);
    }

    ~FixedThickness() {
        delete solver;
    }

    const vector<double>& x0() const {
        return x0_;
    }

    /*
     * point - вектор координат резделов слоев
     */
    Result eval(vector<double> point);

    bool continueFind(double sigma, double deltaSigma) {
        cout << "sigma = " << abs(deltaSigma) << endl;
        return abs(deltaSigma) > 1E-13;
    }
};


#endif //MATERIALSOLVER_FIXEDTHICKNESS_H
