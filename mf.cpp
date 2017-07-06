#include<iostream>
#include <cmath>
#include<Eigen/dense>

#include "mf.h"

std::tuple<Eigen::MatrixXf, Eigen::MatrixXf> matfactor(
    Eigen::MatrixXi & R,
    int K,
    float alpha,
    float lambda) {

    Eigen::MatrixXf P = Eigen::MatrixXf::Random(R.rows(), K);
    Eigen::MatrixXf Q = Eigen::MatrixXf::Random(K, R.cols());

    // TODO test with steps then move to eps for error
    int steps = 500;
    for (int step=0; step<steps; step++) {

        // TODO create P and Q here?
        // TODO cols first? arrays stored in Fortran order (i.e., cols)
        for (int row=0; row<R.rows(); row++) {
            for (int col=0; col<R.cols(); col++) {
                if (R(row,col) > 0) {
                    float eij = R(row,col)-P.row(row).dot(Q.col(col));
                    for (int k=0; k<K; k++) {
                        float reg_p = (lambda*Q.row(k)).sum();
                        float reg_q = (lambda*P.col(k)).sum();
                        float p_=P(row,k)+2*alpha*((Q.row(k)*eij).sum()-reg_p);
                        float q_=Q(k,col)+2*alpha*((P.col(k)*eij).sum()-reg_q);
                        P(row,k) = p_;
                        Q(k,col) = q_;
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
        // std::cout << "Iteration : " << step << " ~ error : " << e << std::endl;
    }

    std::tuple<Eigen::MatrixXf, Eigen::MatrixXf> t = std::make_tuple(P,Q);
    return t;
}
