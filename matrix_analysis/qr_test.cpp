/**
 * @file qr_test.cpp
 * @author cggos (cggos@outlook.com)
 * @brief QR Decomposition
 *        SuiteSparseQR实现更好一些，比自带Eigen::SparseQR快50%左右
 * @version 0.1
 * @date 2020-05-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>

#include <Eigen/Core>
#include <Eigen/SPQRSupport>
#include <Eigen/SparseQR>
#include <Eigen/OrderingMethods>

using namespace Eigen;

int main() {

    // 初始化非零元素
    int r[3] = {0, 1, 2};
    int c[3] = {1, 2, 2};
    double val[3] = {6.1, 7.2, 8.3};
    std::vector<Triplet<double>> triplets;
    for (int i = 0; i < 3; ++i)
        triplets.emplace_back(r[i], c[i], val[i]);

    // 初始化稀疏矩阵
    SparseMatrix<double> A(4, 4);
    A.setFromTriplets(triplets.begin(), triplets.end());
    std::cout << "A = \n" << A << std ::endl;

    // set ordering methods
    AMDOrdering<double> ordering;
    PermutationMatrix<Dynamic, Dynamic, double> perm;
    ordering(A, perm); // call AMD

    SparseQR<SparseMatrix<double>, AMDOrdering<int>> qr;
    qr.compute(A);
    
    SparseMatrix<double> Q, R;
    // qr.matrixQ().evalTo(Q);
    Q = qr.matrixQ();
    R = qr.matrixR();

    std::cout << "Q: \n" << Q << std::endl;
    std::cout << "R: \n" << R << std::endl;

    SPQR<SparseMatrix<double>> spqr;
    spqr.compute(A);

    // 求 Ax = b
    Vector4d b(1, 2, 3, 4);
    Vector4d x = spqr.solve(b);
    std::cout << "x  = " << x.transpose() << std::endl;
    std::cout << "Ax = " << (A*x).transpose() << std::endl;

    std::cout << std::endl;

    return 0;
}
