#include<iostream>
#include <cmath>
#include<Eigen/dense>

#include "mf.h"

void matfactor(
    Eigen::MatrixXi & R,
    Eigen::MatrixXf & P,
    Eigen::MatrixXf & Q,
    int K,
    float alpha,
    float lambda) {
    // TODO test with steps then move to eps for error
    int steps = 10; // try with 100
    for (int step=0; step<steps; step++) {

        // TODO create P and Q here?
        // TODO cols first? arrays stored in Fortran order (i.e., cols)
        for (int row=0; row<R.rows(); row++) {
            for (int col=0; col<R.cols(); col++) {
                if (R(row,col) > 0) {
                    float eij = R(row,col)-P.row(row).dot(Q.col(col));
                    std::cout << " eij is " << eij << std::endl;
                    for (int k=0; k<K; k++) {
                        // get updated p and q values
                        float p_=P(row,k)-2*alpha*(Q.row(k)*eij).sum()+(lambda*Q.row(k)).sum();
                        float q_=Q(k,col)-2*alpha*(P.col(k)*eij).sum()+(lambda*P.col(k)).sum(); 
                        P(row,k) = p_;
                        Q(k, col) = q_;
                    }
                }
            }
        }

        Eigen::MatrixXf R_ = P*Q;
        float e = 0;
        for (int row=0; row<R.rows(); row++) {
            for (int col=0; col<R.cols(); col++) {
                if (R(row,col) > 0) {
                    e += std::pow(R(row,col)-P.row(row).dot(Q.col(col)), 2);
                    for (int k=0; k<K; k++) {
                        e += lambda*std::pow( std::pow(P(row,k),2)+std::pow(Q(k,col),2) ,2);
                    }
                }
            }
        }
        // TODO why is going to inf
        std::cout << "Iteration : " << step << " ~ error : " << e << std::endl;
    }
}
