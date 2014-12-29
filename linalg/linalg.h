#ifndef LINALG_H_INCLUDED
#define LINALG_H_INCLUDED

#include "matrix.h"
#include "matrix_operations.h"
#include "quaternion.h"
#include "quaternion_operations.h"
#include "vector.h"
#include "vector_operations.h"
#include "transforms.h"

typedef LinAlg::Matrix<2, 2, float> Matrix2x2;
typedef LinAlg::Matrix<2, 3, float> Matrix2x3;
typedef LinAlg::Matrix<2, 4, float> Matrix2x4;
typedef LinAlg::Matrix<3, 2, float> Matrix3x2;
typedef LinAlg::Matrix<3, 3, float> Matrix3x3;
typedef LinAlg::Matrix<3, 4, float> Matrix3x4;
typedef LinAlg::Matrix<4, 2, float> Matrix4x2;
typedef LinAlg::Matrix<4, 3, float> Matrix4x3;
typedef LinAlg::Matrix<4, 4, float> Matrix4x4;
typedef LinAlg::Vector<2, float> Vector2;
typedef LinAlg::Vector<3, float> Vector3;
typedef LinAlg::Vector<4, float> Vector4;
typedef LinAlg::Quaternion<float> Quaternion;

#endif // LINALG_H_INCLUDED
