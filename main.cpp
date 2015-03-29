#include <iostream>
#include "Eigen/Dense"
#include "MaterialSolver.h"

using namespace std;
using namespace Eigen;

// sample usage
double f(double x) { return x*x; }

int main() {
//    Matrix3f A;
//    Vector3f b;
//    A << 1,2,3,  4,5,6,  7,8,10;
//    b << 3, 3, 4;
//    cout << "Here is the matrix A:\n" << A << endl;
//    cout << "Here is the vector b:\n" << b << endl;
//    Vector3f x = A.colPivHouseholderQr().solve(b);
//    cout << "The solution is:\n" << x << endl;
//
//
//
//    // inside a function somewhere:
//    int steps = 1000;
//    double rl = integrate(f, 0.0, 1.0, steps, rectangular(rectangular::left));
//    double rm = integrate(f, 0.0, 1.0, steps, rectangular(rectangular::middle));
//    double rr = integrate(f, 0.0, 1.0, steps, rectangular(rectangular::right));
//    double t  = integrate(f, 0.0, 1.0, steps, trapezium());
//    double s  = integrate(f, 0.0, 1.0, steps, simpson());
//
//    cout << rl << endl;
//    cout << rm << endl;
//    cout << rr << endl;
//    cout << t << endl;
//    cout << s << endl;
    int N = 2;
    double* y = new double[N]{0.2,0.3};
    double* k = new double[N]{1.2,1.1};
    MaterialSolver solver(N, y, k, 0, 1200);
    solver.start();
}