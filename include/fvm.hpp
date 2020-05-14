#ifndef _FVM_
#define _FVM_

#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

typedef vector<double> vec;

class Fvm
{
private:
    int node;
    vector<vec> A;
    vec b;
    vec Temp;
    vec nu;

public:
    Fvm(int node_, vec Temp_, vec nu_);

    Fvm();

    ~Fvm();

    vec grad(int TL, int TH);

    vec interp();

    void assembly(double dx, double TL, double TH);

    VectorXd solve();

};

#endif
