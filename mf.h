#include<tuple>
#include<iostream>
#include<Eigen/dense>

std::tuple<Eigen::MatrixXf,Eigen::MatrixXf> matfactor(
    Eigen::MatrixXi & R,
    int K,
    float alpha,
    float lambda);
