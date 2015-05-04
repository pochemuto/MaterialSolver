#include <iostream>
#include <vector>
#include "Eigen/Dense"
#include "MaterialSolver.h"
#include "sqlite3pp/sqlite3pp.h"
#include "Database.h"
#include "function/FixedThickness.h"
#include "minimizer/CompassSearch.h"

using namespace std;
using namespace Eigen;

// sample usage
double f(double x) { return x*x; }

int main() {
    Material ceramic(2, 360, 0.215, 12E-6);
    Material nickel(40, 120, 0.3, 15E-6);
    Material steel(20, 200, 0.3, 15.7E-6);

//    vector<Layer> layers;
//    layers.push_back(Layer(nickel, 10E-6));
//    layers.push_back(Layer(ceramic, 10E-6));
//    layers.push_back(Layer(nickel, 2E-6));
//    layers.push_back(Layer(ceramic, 10E-6 / 10));
//    layers.push_back(Layer(nickel, 2E-6));
//    layers.push_back(Layer(ceramic, 10E-6 / 5));
//    layers.push_back(Layer(steel, 1000E-6));
//
//    MaterialSolver solver(layers, 1200, 1000);
//    solver.start();
//
//    Database db("data.db");
//    int cid = (int) db.storeConfiguration(layers, 1200, 1000);
//    db.storeFunctionT(cid, solver.functionT());
//    db.storeFunctionV(cid, solver.functionV());
//    db.storeFunctionSigmaX(cid, solver.functionSigmaX());

    Layer bottom = Layer(steel, 10);
    FixedThickness fi(nickel, ceramic, bottom, 1200, 1000, 5, 30);
    Result startValue = fi.eval(fi.x0());
    cout.precision(15);
    cout << "Start from sigma = " << startValue << endl;

    CompassSearch<FixedThickness> search(fi, fi.x0(), 1);
    vector<double> minimum = search.search();
    Result result = fi.eval(minimum);
    cout << "End with sigma = " << result << endl;

    return 0;
}