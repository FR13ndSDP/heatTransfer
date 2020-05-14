#ifndef _FVM_
#define _FVM_

#include <vector>
#include <Eigen/Dense>

using namespace std;

typedef vector<double> vec;

class Fvm
{
private:
    int node;       // 节点数
    vector<vec> A;  // 系数矩阵
    vec b;          // 源项
    vec Temp;       // 温度向量
    vec nu;         // 导热系数向量

public:
    // 构造函数
    Fvm(int node_, vec Temp_, vec nu_);

    // 析构函数
    ~Fvm();

    // 梯度算子
    vec grad(int TL, int TH);

    // 导热系数面上插值
    vec interp();

    // 组装系数矩阵及源项
    void assembly(double dx, double TL, double TH);

    // 使用Eigen库解线性方程组
    Eigen::VectorXd solve();

};

#endif
