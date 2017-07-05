#include<iostream>
#include<Eigen/dense>

void matfactor(
    Eigen::MatrixXi & R,
    Eigen::MatrixXf & P,
    Eigen::MatrixXf & Q,
    int K,
    float alpha,
    float lambda);
