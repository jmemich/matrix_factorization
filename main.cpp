#include<iostream>
#include<Eigen/dense>

#include "mf.h"

using namespace Eigen;

int main() {

    int K = 2; // Number of latent factors
    float alpha = 0.0001; // step size
    float lambda = 0.02; // regularization strength

    // matrix to approximate
    // TODO make this for floats. figure out how to check non-missing values
    // TODO i.e., use sparse matrix encoding
    Eigen::MatrixXi R(5,4);
    R << 5,3,0,1,
         4,0,0,1,
         1,1,0,5,
         1,0,0,4,
         0,1,5,4;

    // ~randomly initialized factorization matrixes with K latent features
    // TODO make these all zeros?
    Eigen::MatrixXf P(5,K);
    Eigen::MatrixXf Q(K,4);
    P << 1,1,
         1,1,
         1,1,
         1,1,
         1,1;
    Q << 1,1,1,1,
         1,1,1,1;

    matfactor(R,P,Q,K,alpha,lambda);

    return 0;
}
