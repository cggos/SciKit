#include <ctime>
#include <iostream>

// #define EIGEN_USE_MKL_ALL
// #define EIGEN_VECTORIZE_SSE4_2

// #include <omp.h>
#include <Eigen/Dense>

#include "tic_toc.h"

using namespace Eigen;

#define matrix_mul3(D, A, B, C)                             \
    {                                                       \
        D = MatrixXd::Zero(A.rows(), C.cols());             \
        MatrixXd temp = MatrixXd::Zero(A.rows(), B.cols()); \
        for (int i = 0; i < temp.cols(); i++) {             \
            temp.col(i) = A * B.col(i);                     \
        }                                                   \
        for (int i = 0; i < D.cols(); i++) {                \
            D.col(i) = temp * C.col(i);                     \
        }                                                   \
    }

int main() {
    // omp_set_num_threads(8);
    std::cout << "nbThreads: " << Eigen::nbThreads() << "\n";

    // srand((unsigned)time(NULL));
    // Eigen::MatrixXd randvalue = (Eigen::MatrixXd::Random(4, 4)).array().abs() * 2 * M_PI;
    // std::cout << randvalue << std::endl;
    // std::cout << std::endl;
    // Eigen::MatrixXcd randvalue2 = Eigen::MatrixXcd::Random(4, 4);
    // std::cout << randvalue2 << std::endl;

    const int MAT_DIM = 100;

    // Eigen::MatrixXd A1 = Eigen::MatrixXd::Random(MAT_DIM, MAT_DIM);
    // Eigen::MatrixXd B1 = Eigen::MatrixXd::Random(MAT_DIM, MAT_DIM);
    // Eigen::MatrixXd C1 = Eigen::MatrixXd::Zero(MAT_DIM, MAT_DIM);
    // Eigen::MatrixXd D1 = Eigen::MatrixXd::Zero(MAT_DIM, MAT_DIM);

    Eigen::Matrix<double, MAT_DIM, MAT_DIM> A1 = Eigen::Matrix<double, MAT_DIM, MAT_DIM>::Random();
    Eigen::Matrix<double, MAT_DIM, MAT_DIM> B1 = Eigen::Matrix<double, MAT_DIM, MAT_DIM>::Random();
    Eigen::Matrix<double, MAT_DIM, MAT_DIM> C1 = Eigen::Matrix<double, MAT_DIM, MAT_DIM>::Zero();
    Eigen::Matrix<double, MAT_DIM, MAT_DIM> D1 = Eigen::Matrix<double, MAT_DIM, MAT_DIM>::Zero();

    TicToc t_mul001;
    B1 = (A1 * B1).eval();
    printf("[cggos time] t_mul001: %fms\n", t_mul001.toc());

    TicToc t_mul002;
    B1.transpose() *= A1.transpose();
    printf("[cggos time] t_mul002: %fms\n", t_mul002.toc());

    TicToc t_mul01;
    C1.noalias() = A1 * B1;
    printf("[cggos time] t_mul01: %fms\n", t_mul01.toc());

    TicToc t_mul02;
    for (int i = 0; i < C1.cols(); ++i) C1.col(i) = A1 * B1.col(i);
    printf("[cggos time] t_mul02: %fms\n", t_mul02.toc());

    TicToc t_mul03;
    D1 = A1 * B1 * C1;
    printf("[cggos time] t_mul03: %fms\n", t_mul03.toc());

    TicToc t_mul04;
    matrix_mul3(D1, A1, B1, C1);
    printf("[cggos time] t_mul04: %fms\n", t_mul04.toc());

    TicToc t_mul;
    // C1 += A1.transpose() * B1; // 17.75ms  --openmp-->  3~6ms
    C1.noalias() += A1.transpose() * B1;  // 16.48ms  --openmp-->  4.3ms
    printf("[cggos time] t_mul: %fms\n", t_mul.toc());

    return 0;
}