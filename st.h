#pragma once


#include  "iostream"
//#include  "math_headers.h"
typedef double ScalarType;

#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/Sparse"
#include <unsupported/Eigen/SparseExtra>
#include <unsupported/Eigen/KroneckerProduct>

// global header
//#include "global_headers.h"

// glm
//#include "glm.hpp"
//#include "gtc\matrix_transform.hpp"

// omp
//#include <omp.h>

// eigen vectors and matrices
typedef int IndexType;
typedef unsigned int uint;
typedef Eigen::Matrix<ScalarType, 2, 2, 0, 2, 2> EigenMatrix2;//行列の数オプション型の名前
typedef Eigen::Matrix<ScalarType, 3, 3, 0, 3, 3> EigenMatrix3;
typedef Eigen::Matrix<ScalarType, 4, 4, 0, 4, 4> EigenMatrix4;
typedef Eigen::Matrix<ScalarType, 2, 1, 0, 2, 1> EigenVector2;
typedef Eigen::Matrix<ScalarType, 3, 1, 0, 3, 1> EigenVector3;
typedef Eigen::Matrix<ScalarType, 4, 1, 0, 4, 1> EigenVector4;
typedef Eigen::Matrix<ScalarType, 9, 1, 0, 9, 1> EigenVector9;
typedef Eigen::Matrix<ScalarType, Eigen::Dynamic, 1> EigenVectorX;
typedef Eigen::Matrix<ScalarType, Eigen::Dynamic, 3> EigenMatrix3X;
typedef Eigen::Matrix<ScalarType, Eigen::Dynamic, Eigen::Dynamic> EigenMatrixXs;
typedef Eigen::Matrix<IndexType, Eigen::Dynamic, Eigen::Dynamic>  EigenMatrixXi;
typedef Eigen::Quaternion<ScalarType> EigenQuaternion;
typedef Eigen::SparseMatrix<ScalarType>      SparseMatrix;
typedef Eigen::Triplet<ScalarType, IndexType> SparseMatrixTriplet;




