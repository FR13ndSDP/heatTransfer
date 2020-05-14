#include <iostream>
#include <fstream>
#include "fvm.cpp"

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        cout << "No enough parameter to solve" << endl
             << "parameter lis:" << endl
             << "nNode\t" << "number of nodes" << endl
             << "dx\t"    << "size of node" << endl
             << "TL\t"    << "temrature at beginning side" << endl
             << "TH\t"    << "temprature at other side" << endl;
        return -1;
    }

    else
    {
        // 传入参数;
        int nNode = atoi(argv[1]);
        double dx = atof(argv[2]);
        double TL = atof(argv[3]);
        double TH = atof(argv[4]);

        vec temp(nNode, 0);
        vec nu(nNode, 0);

        // 非均匀导热系数分布
        for (int i = 0; i < nNode; i++)
        {
            nu[i] = 100 + i * 500.0/nNode;
        }

        Fvm fvm(nNode, temp, nu);
        fvm.assembly(dx, TL, TH);

        Eigen::VectorXd x = fvm.solve();

        ofstream fout("output.dat");
        fout<<x<<endl;
        return 0;
    }
}