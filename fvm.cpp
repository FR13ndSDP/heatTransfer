#include "./include/fvm.hpp"

Fvm::Fvm(int node_, vec Temp_, vec nu_) : node(node_), Temp(Temp_), nu(nu_)
{
    vector<vec> AA(node, vec(node, 0)); // node方阵，初始化为零
    A = AA;
    vec bb(node, 0);      
    b = bb;             // node向量，初始化为零
}

Fvm::Fvm()
{
    vector<vec> A(node, vec(node, 0)); // node方阵，初始化为零
    vec b(node, 0);                    // node向量，初始化为零
}

Fvm::~Fvm()
{}

vec Fvm::grad(int TL, int TH)
{
    Temp.push_back(TH);
    Temp.insert(Temp.begin(), TL);
    vec grad;
    for (int i = 0; i < Temp.size() - 1; i++)
    {
        grad.push_back(Temp[i + 1] - Temp[i]);
    }
    return grad;
}

vec Fvm::interp()
{
    nu.push_back(*(nu.end() - 1));
    nu.insert(nu.begin(), *nu.begin());
    vec nuf;
    for (int i = 0; i < nu.size() - 1; i++)
    {
        nuf.push_back((nu[i + 1] + nu[i]) / 2);
    }
    return nuf;
}

void Fvm::assembly(double dx, double TL, double TH)
{
    vec nuf = interp();
    for (int i = 1; i < node - 1; i++)
    {
        A[i][i - 1] = nuf[i] / dx;
        A[i][i] = -(nuf[i] + nuf[i + 1]) / dx;
        A[i][i + 1] = nuf[i + 1] / dx;
    }

    A[0][1] = nuf[1] / dx;
    b[0] = -2 * nuf[0] / dx * TL;
    A[0][0] = -A[0][1] + b[0] / TL;

    A[node - 1][node - 2] = nuf[node - 1] / dx;
    b[node - 1] = -2 * nuf[node] / dx * TH;
    A[node - 1][node - 1] = -A[node - 1][node - 2] + b[node - 1] / TH;
}

VectorXd Fvm::solve()
{
    MatrixXd Ax(node, node);
    VectorXd bx(node);
    for (int i = 0;i<node;i++)
    {
        for (int j = 0;j< node; j++)
        {
            Ax(i,j)=A[i][j];
        }
        bx(i) = b[i];
    }
    return Ax.lu().solve(bx);
}
