#include<iostream>
#include<Eigen/dense>

#include "mf.h"

using namespace Eigen;

int main() {

    int K = 2; // Number of latent factors
    float alpha = 0.0001; // step size
    float lambda = 0.02; // regularization strength

    // TODO use sparse matrix
    Eigen::MatrixXi R(5,4); // matrix to approximate
    R << 5,3,0,1,
         4,0,0,1,
         1,1,0,5,
         1,0,0,4,
         0,1,5,4;

    std::tuple<Eigen::MatrixXf,Eigen::MatrixXf> t = matfactor(R,K,alpha,lambda);
    Eigen::MatrixXf P = std::get<0>(t);
    Eigen::MatrixXf Q = std::get<1>(t);
    std::cout << "R^ :" << P*Q << std::endl;

    return 0;
}
