#include <iostream>
#include <vector>
#include "Eigen/Dense"
#include "MaterialSolver.h"
#include "sqlite3pp/sqlite3pp.h"
#include "Database.h"

using namespace std;
using namespace Eigen;

// sample usage
double f(double x) { return x*x; }

int main() {
    Material ceramic(2, 360, 0.215, 12E-6);
    Material nickel(40, 120, 0.3, 15E-6);

    vector<Layer> layers;
    layers.push_back(Layer(nickel, 2E-6));
    layers.push_back(Layer(ceramic, 10E-6));
    layers.push_back(Layer(nickel, 2E-6));

    MaterialSolver solver(layers, 1200, 1000);
    solver.start();

    double y;
    int n = 0, steps = 10;
    while (y <= solver.getH()) {
        cout << y << endl;
        cout << solver.getT(y) << endl;
        n++;
        y = solver.getH() / steps * n;
    }

    Database db("data.db");
    int cid = db.storeConfiguration(layers, 1200, 1000);
    db.storeFunctionT(cid, solver.functionT());
    db.storeFunctionV(cid, solver.functionV());

    return 0;
}