#include <iostream>
#include <vector>
#include "Eigen/Dense"
#include "MaterialSolver.h"
#include "sqlite3pp/sqlite3pp.h"

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

    double y;
    int n = 0, steps = 10;
    while (y <= solver.getH()) {
        cout << y << endl;
        cout << solver.getT(y) << endl;
        n++;
        y = solver.getH() / steps * n;
    }

    sqlite3pp::database db("test.db");
    db.execute("CREATE TABLE contacts (name TEXT, value DOUBLE)");

    sqlite3pp::command cmd(db, "INSERT INTO contacts (name, value) VALUES (:name, :value)");
    cmd.bind(":name", "Alex");
    cmd.bind(":value", 123.43);
    cmd.execute();

    return 0;
}