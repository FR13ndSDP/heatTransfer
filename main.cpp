#include <iostream>
#include "fvm.cpp"

int main()
{
    //线性方程求解 Ax =B;
    int nNode = 5;
    double dx = 0.1;
    double TL = 100.0;
    double TH = 500.0;

    vec temp(nNode, 0);
    vec nu(nNode, 1000);
    for (int i = 0; i<5;i++)
    {
        nu[i] = 100+i*100;
    }

    Fvm fvm(nNode, temp, nu);
    fvm.assembly(dx, TL, TH);

    VectorXd x = fvm.solve();

    cout << x<< endl;
    return 0;
}