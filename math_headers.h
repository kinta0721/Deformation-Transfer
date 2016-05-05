#ifndef _MATH_HEADERS_H_


#define _MATH_HEADERS_H_

// definitions
#define HIGH_PRECISION

// single or double presicion
#ifdef HIGH_PRECISION
typedef double ScalarType;
#define TW_TYPE_SCALAR_TYPE TW_TYPE_DOUBLE
#else
typedef float ScalarType;
#define TW_TYPE_SCALAR_TYPE TW_TYPE_FLOAT
#endif

// small number and large number
#ifdef HIGH_PRECISION
#define EPSILON 1e-15
#else
#define EPSILON 1e-6
#endif

#define LARGER_EPSILON 1e-6

// eigen
#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/Sparse"
#include <unsupported/Eigen/SparseExtra>
#include <unsupported/Eigen/KroneckerProduct>

#include <vector>
// eigen vectors and matrices
typedef int IndexType;
typedef unsigned int uint;
typedef Eigen::Matrix<ScalarType, 2, 2, 0, 2, 2> EigenMatrix2;//行列の数オプション型の名前
typedef Eigen::Matrix<ScalarType, 3, 3, 0, 3, 3> EigenMatrix3;
typedef Eigen::Matrix<ScalarType, 3, 2, 0, 3, 2> EigenMatrix32;
typedef Eigen::Matrix<ScalarType, 2, 3, 0, 2, 3> EigenMatrix23;
typedef Eigen::Matrix<ScalarType, 2, 1, 0, 2, 1> EigenVector2;
typedef Eigen::Matrix<ScalarType, 3, 1, 0, 3, 1> EigenVector3;
typedef Eigen::Matrix<ScalarType, Eigen::Dynamic, 1> EigenVectorX;
typedef Eigen::Matrix<ScalarType, Eigen::Dynamic, 3> EigenMatrix3X;
typedef Eigen::Matrix<ScalarType, Eigen::Dynamic, Eigen::Dynamic> EigenMatrixXs;



typedef Eigen::Triplet<double> T;
typedef Eigen::SparseMatrix<double> SparseMartix;


#endif