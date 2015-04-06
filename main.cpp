#include <iostream>
#include <vector>
#include "Eigen/Dense"
#include "MaterialSolver.h"

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

    MaterialSolver solver(layers, 1200, 1000);
    solver.start();
}