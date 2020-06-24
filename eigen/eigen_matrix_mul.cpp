#include <ctime>
#include <iostream>

// #define EIGEN_USE_MKL_ALL
// #define EIGEN_VECTORIZE_SSE4_2

// #include <omp.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <opencv2/core/core.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "tic_toc.h"

using namespace Eigen;

// #define matrix_mul3(D, A, B, C)                             \
//     {                                                       \
//         D = MatrixXd::Zero(A.rows(), C.cols());             \
//         MatrixXd temp = MatrixXd::Zero(A.rows(), B.cols()); \
//         for (int i = 0; i < temp.cols(); i++) {             \
//             temp.col(i) = A * B.col(i);                     \
//         }                                                   \
//         for (int i = 0; i < D.cols(); i++) {                \
//             D.col(i) = temp * C.col(i);                     \
//         }                                                   \
//     }

void matrix_mul(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B, Eigen::MatrixXd &C) {
    C = Eigen::MatrixXd::Zero(A.rows(), B.cols());
    for (int i = 0; i < C.rows(); i++) for (int j = 0; j < C.cols(); j++) C(i, j) = A.row(i) * B.col(j);
}

void matrix_mul(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B, const Eigen::MatrixXd &C, Eigen::MatrixXd &D) {
    D = Eigen::MatrixXd::Zero(A.rows(), C.cols());
    Eigen::MatrixXd AB = Eigen::MatrixXd::Zero(A.rows(), B.cols());
    for (int i = 0; i < AB.cols(); i++) AB.col(i) = A * B.col(i);
    for (int i = 0; i < D.cols(); i++) D.col(i) = AB * C.col(i);
}

int main() {

#if (defined __ARM_NEON) || (defined __ARM_NEON__)
    printf("ARM_NEON detected\n");
#else
    printf("ARM_NEON NOT detected\n");
#endif

#if defined EIGEN_VECTORIZE
    printf("EIGEN_VECTORIZE enabled\n");
#else
    printf("EIGEN_VECTORIZE NOT enabled\n");
#endif

#if defined EIGEN_VECTORIZE_NEON
    printf("EIGEN_VECTORIZE_NEON enabled\n");
#else
    printf("EIGEN_VECTORIZE_NEON NOT enabled\n");
#endif

#if defined EIGEN_VECTORIZE_SSE2
    printf("EIGEN_VECTORIZE_SSE2 enabled\n");
#else
    printf("EIGEN_VECTORIZE_SSE2 NOT enabled\n");
#endif

    // omp_set_num_threads(8);
    printf("Eigen::nbThreads(): %d\n", Eigen::nbThreads());
    printf("EIGEN_MAX_ALIGN_BYTES: %d\n", EIGEN_MAX_ALIGN_BYTES);
    printf("EIGEN_MAX_STATIC_ALIGN_BYTES: %d\n", EIGEN_MAX_STATIC_ALIGN_BYTES);
    printf("EIGEN_STACK_ALLOCATION_LIMIT: %dKB\n", EIGEN_STACK_ALLOCATION_LIMIT / 1024); // 128KB
    std::cout << "===================================================" << std::endl;

    // srand((unsigned)time(NULL));
    // Eigen::MatrixXd randvalue = (Eigen::MatrixXd::Random(4, 4)).array().abs() * 2 * M_PI;
    // std::cout << randvalue << std::endl;
    // std::cout << std::endl;
    // Eigen::MatrixXcd randvalue2 = Eigen::MatrixXcd::Random(4, 4);
    // std::cout << randvalue2 << std::endl;

    const int MAT_DIM = 500;
    Eigen::MatrixXd A1 = Eigen::MatrixXd::Random(MAT_DIM, MAT_DIM);
    Eigen::MatrixXd B1 = Eigen::MatrixXd::Random(MAT_DIM, MAT_DIM);
    Eigen::MatrixXd C1 = Eigen::MatrixXd::Zero(MAT_DIM, MAT_DIM);
    Eigen::MatrixXd D1 = Eigen::MatrixXd::Zero(MAT_DIM, MAT_DIM);

    // const int MAT_DIM = 100;
    // Eigen::Matrix<double, MAT_DIM, MAT_DIM> A1 = Eigen::Matrix<double, MAT_DIM, MAT_DIM>::Random();
    // Eigen::Matrix<double, MAT_DIM, MAT_DIM> B1 = Eigen::Matrix<double, MAT_DIM, MAT_DIM>::Random();
    // Eigen::Matrix<double, MAT_DIM, MAT_DIM> C1 = Eigen::Matrix<double, MAT_DIM, MAT_DIM>::Zero();
    // Eigen::Matrix<double, MAT_DIM, MAT_DIM> D1 = Eigen::Matrix<double, MAT_DIM, MAT_DIM>::Zero();

    TicToc t_010;
    B1 = (A1 * B1).eval();
    printf("[cggos time] t_010: %fms\n", t_010.toc());

    TicToc t_011;
    B1.transpose() *= A1.transpose();
    printf("[cggos time] t_011: %fms\n", t_011.toc());

    TicToc t_012;
    C1.noalias() = A1 * B1;
    printf("[cggos time] t_012: %fms\n", t_012.toc());

    TicToc t_013;
    for (int i = 0; i < C1.cols(); ++i) C1.col(i) = A1 * B1.col(i);
    printf("[cggos time] t_013: %fms\n", t_013.toc());

    TicToc t_014;
    D1 = A1 * B1 * C1;
    printf("[cggos time] t_014: %fms\n", t_014.toc());

    TicToc t_015;
    matrix_mul(A1, B1, C1, D1);
    printf("[cggos time] t_015: %fms\n", t_015.toc());

    TicToc t_016;
    // C1 += A1.transpose() * B1; // 17.75ms  --openmp-->  3~6ms
    C1.noalias() += A1.transpose() * B1;  // 16.48ms  --openmp-->  4.3ms
    printf("[cggos time] t_016: %fms\n", t_016.toc());

    std::cout << "===================================================" << std::endl;

    TicToc t_020;
    C1 = A1 * B1;
    printf("[cggos time] t_020: %fms\n", t_020.toc());

    Eigen::MatrixXd A20 = Eigen::MatrixXd::Identity(MAT_DIM, MAT_DIM);

    for (int i = 0; i < MAT_DIM; i++)
        for (int j = i; j < MAT_DIM; j++) A20(i, j) = i + j;
    Eigen::MatrixXd A20tri = A20.triangularView<Upper>();

    SparseMatrix<double, RowMajor> A20s = A20.sparseView();  // RowMajor

    TicToc t_021;
    C1 = A20 * B1;
    printf("[cggos time] t_021: %fms\n", t_021.toc());

    std::cout << "===================================================" << std::endl;

    cv::Mat mat_src = cv::imread("../../data/00305_01_144_161.png", cv::ImreadModes::IMREAD_ANYCOLOR);
    Eigen::MatrixXd A30;
    cv::cv2eigen(mat_src, A30);

    Eigen::MatrixXd B30 = Eigen::MatrixXd::Random(A30.cols(), A30.cols());

    TicToc t_030;
    // SparseMatrix<double, RowMajor> A30s = A30.sparseView();
    Eigen::MatrixXd C30 = A30 * B30;
    printf("[cggos time] t_030: %fms\n", t_030.toc());

    std::cout << "===================================================" << std::endl;

    Eigen::MatrixXd A40 = Eigen::MatrixXd::Random(80, 1000);
    Eigen::MatrixXd B40 = Eigen::MatrixXd::Random(1000, 80);

    Eigen::MatrixXd C40;

    TicToc t_040;
    C40 = A40 * B40;
    printf("[cggos time] t_040: %fms\n", t_040.toc());

    TicToc t_041;
    C40 = B40 * A40;
    // matrix_mul(B40, A40, C40);
    printf("[cggos time] t_041: %fms\n", t_041.toc());

    Eigen::Matrix<double, 80, 80> tmp = Eigen::Matrix<double, 80, 80>::Identity();
    Eigen::MatrixXd At = tmp * A40;

    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor, 16, 1000> A400; // 静态分配内存
    // A400 = A40;

    return 0;
}