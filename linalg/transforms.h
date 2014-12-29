#ifndef LINALG_TRANSFORMS_H_INCLUDED
#define LINALG_TRANSFORMS_H_INCLUDED

#include "vector.h"
#include "vector_operations.h"
#include "matrix.h"
#include "quaternion.h"
#include "quaternion_operations.h"

namespace LinAlg {

// Interface //

template<unsigned n, unsigned m, typename T> Vector<m, T> operator*(const Vector<n, T>& a, const Matrix<n, m, T>& b);
template<unsigned n, unsigned m, typename T> Vector<n, T> operator*(const Matrix<n, m, T>& a, const Vector<m, T>& b);
template<unsigned n, typename T> Vector<n, T> Transform(const Vector<n, T>& a, const Matrix<n+1, n+1, T>& b, const T& c = T(1));
template<unsigned n, typename T> Vector<n, T> Transform(const Matrix<n+1, n+1, T>& a, const Vector<n, T>& b, const T& c = T(1));
template<typename T> Vector<3, T> Rotate(const Quaternion<T>& a, const Vector<3, T>& b);
template<typename T> Matrix<2, 2, T> RotationMatrix2x2(const T& a);
template<typename T> Matrix<3, 3, T> RotationMatrix3x3(const Quaternion<T>& a);
template<typename T> Matrix<4, 4, T> RotationMatrix4x4(const Quaternion<T>& a);
template<typename T> Matrix<4, 4, T> TranslationMatrix4x4(const Vector<3, T>& a);
template<typename T> Matrix<3, 3, T> AxisAngleMatrix3x3(const Vector<3, T>& axis, const T& angle);
template<typename T> Matrix<4, 4, T> AxisAngleMatrix4x4(const Vector<3, T>& axis, const T& angle);
template<typename T> Matrix<4, 4, T> OrthoMatrix4x4(const T& aspectRatio, const T& zoom, const T& farPlane, const T& nearPlane);
template<typename T> Matrix<4, 4, T> PerspectiveMatrix4x4(const T& aspectRatio, const T& fovy, const T& farPlane, const T& nearPlane);
template<typename T> Matrix<4, 4, T> ViewMatrix4x4(const Vector<3, T>& target, const Vector<3, T>& top, const Vector<3, T>& direction, const T& distance);
template<typename T> Quaternion<T> AxisAngleQuaternion(const Vector<3, T>& axis, const T& angle);
template<typename T> Quaternion<T> Matrix3x3ToQuaternion(const Matrix<3, 3, T>& a);
template<typename T> Quaternion<T> Matrix4x4ToQuaternion(const Matrix<4, 4, T>& a);




// Implementation //

template<unsigned n, unsigned m, typename T>
inline Vector<m, T> operator*(const Vector<n, T>& a, const Matrix<n, m, T>& b) {
    if(n == 0) return Vector<m, T>();
    Vector<m, T> result;
    for(unsigned i = 0; i < m; ++i) {
        result[i] = a[0] * b[0][i];
        for(unsigned j = 1; j < n; ++j) {
            result[i] += a[j] * b[j][i];
        }
    }
    return result;
}

template<unsigned n, unsigned m, typename T>
inline Vector<n, T> operator*(const Matrix<n, m, T>& a, const Vector<m, T>& b) {
    if(m == 0) return Vector<n, T>(T(0));
    Vector<n, T> result;
    for(unsigned i = 0; i < n; ++i) {
        result[i] = a[i][0] * b[0];
        for(unsigned j = 1; j < m; ++j) {
            result[i] += a[i][j] * b[j];
        }
    }
    return result;
}

template<typename T>
inline Vector<3, T> Rotate(const Quaternion<T>& a, const Vector<3, T>& b) {
    Quaternion<T> temp = a * Quaternion<T>(0, b[0], b[1], b[2]) * Conjugate(a);
    return Vector<3, T>(temp[1], temp[2], temp[3]);
}

template<unsigned n, typename T>
inline Vector<n, T> Transform(const Vector<n, T>& a, const Matrix<n+1, n+1, T>& b, const T& c) {
    Vector<n+1, T> temp = MakeHomogeneous(a, c) * b;
    return (c == 0) ? Vector<n, T>(temp.data) : HomogeneousDivide(temp);
}

template<unsigned n, typename T>
inline Vector<n, T> Transform(const Matrix<n+1, n+1, T>& a, const Vector<n, T>& b, const T& c) {
    Vector<n+1, T> temp = a * MakeHomogeneous(b, c);
    return (c == 0) ? Vector<n, T>(temp.data) : HomogeneousDivide(temp);
}

template<typename T>
inline Matrix<2, 2, T> RotationMatrix2x2(const T& a) {
    T sina = std::sin(a);
    T cosa = std::cos(a);

    Matrix<2, 2, T> result;
    result[0][0] = cosa;
    result[0][1] = -sina;
    result[1][0] = sina;
    result[1][1] = cosa;
    return result;
}

template<typename T>
Matrix<3, 3, T> RotationMatrix3x3(const Quaternion<T>& a) {
    Matrix<3, 3, T> result;
    result[0][0] = 1 - 2*(a[2]*a[2] + a[3]*a[3]);
    result[0][1] = 2*(a[1]*a[2] - a[3]*a[0]);
    result[0][2] = 2*(a[1]*a[3] + a[2]*a[0]);
    result[1][0] = 2*(a[1]*a[2] + a[3]*a[0]);
    result[1][1] = 1 - 2*(a[1]*a[1] + a[3]*a[3]);
    result[1][2] = 2*(a[2]*a[3] - a[1]*a[0]);
    result[2][0] = 2*(a[1]*a[3] - a[2]*a[0]);
    result[2][1] = 2*(a[2]*a[3] + a[1]*a[0]);
    result[2][2] = 1 - 2*(a[1]*a[1] + a[2]*a[2]);
    return result;
}

template<typename T>
Matrix<4, 4, T> RotationMatrix4x4(const Quaternion<T>& a) {
    Matrix<4, 4, T> result(T(1));
    result[0][0] = 1 - 2*(a[2]*a[2] + a[3]*a[3]);
    result[0][1] = 2*(a[1]*a[2] - a[3]*a[0]);
    result[0][2] = 2*(a[1]*a[3] + a[2]*a[0]);
    result[1][0] = 2*(a[1]*a[2] + a[3]*a[0]);
    result[1][1] = 1 - 2*(a[1]*a[1] + a[3]*a[3]);
    result[1][2] = 2*(a[2]*a[3] - a[1]*a[0]);
    result[2][0] = 2*(a[1]*a[3] - a[2]*a[0]);
    result[2][1] = 2*(a[2]*a[3] + a[1]*a[0]);
    result[2][2] = 1 - 2*(a[1]*a[1] + a[2]*a[2]);
    return result;
}

template<typename T>
Matrix<4, 4, T> TranslationMatrix4x4(const Vector<3, T>& a) {
    Matrix<4, 4, T> result(T(1));
    result[0][3] = a[0];
    result[1][3] = a[1];
    result[2][3] = a[2];
    return result;
}

template<typename T>
Matrix<3, 3, T> AxisAngleMatrix3x3(const Vector<3, T>& axis, const T& angle) {
    Matrix<3, 3, T> result;
    T s = std::sin(angle);
    T c = std::cos(angle);
    T t = T(1) - c;
    result[0][0] = t*axis[0]*axis[0] + c;
    result[0][1] = t*axis[0]*axis[1] - axis[2]*s;
    result[0][2] = t*axis[0]*axis[2] + axis[1]*s;
    result[1][0] = t*axis[0]*axis[1] + axis[2]*s;
    result[1][1] = t*axis[1]*axis[1] + c;
    result[1][2] = t*axis[1]*axis[2] - axis[0]*s;
    result[2][0] = t*axis[0]*axis[2] - axis[1]*s;
    result[2][1] = t*axis[1]*axis[2] + axis[0]*s;
    result[2][2] = t*axis[2]*axis[2] + c;
    return result;
}

template<typename T>
Matrix<4, 4, T> AxisAngleMatrix4x4(const Vector<3, T>& axis, const T& angle) {
    Matrix<4, 4, T> result(T(1));
    T s = std::sin(angle);
    T c = std::cos(angle);
    T t = T(1) - c;
    result[0][0] = t*axis[0]*axis[0] + c;
    result[0][1] = t*axis[0]*axis[1] - axis[2]*s;
    result[0][2] = t*axis[0]*axis[2] + axis[1]*s;
    result[1][0] = t*axis[0]*axis[1] + axis[2]*s;
    result[1][1] = t*axis[1]*axis[1] + c;
    result[1][2] = t*axis[1]*axis[2] - axis[0]*s;
    result[2][0] = t*axis[0]*axis[2] - axis[1]*s;
    result[2][1] = t*axis[1]*axis[2] + axis[0]*s;
    result[2][2] = t*axis[2]*axis[2] + c;
    return result;
}

template<typename T>
Matrix<4, 4, T> OrthoMatrix4x4(const T& aspectRatio,
                               const T& zoom,
                               const T& farPlane,
                               const T& nearPlane)
{
    Matrix<4, 4, T> result(T(1));
    result[0][0] = 2 / aspectRatio * zoom;
    result[1][1] = 2 * zoom;
    result[2][2] = -2 / (farPlane - nearPlane);
    result[3][3] = 1;
    return result;
}

template<typename T>
Matrix<4, 4, T> OrthoMatrix4x4(const T& left,
                               const T& right,
                               const T& bottom,
                               const T& top,
                               const T& zNear,
                               const T& zFar)
{
    Matrix<4, 4, T> result(T(1));
    result[0][0] = 2/(right-left);
    result[1][1] = 2/(top-bottom);
    result[2][2] = -2 /(zFar-zNear);
    result[3][3] = 1;

    result[0][3] = -((right+left)/(right-left));
    result[1][3] = -((top+bottom)/(top-bottom));
    result[2][3] = -((zFar+zNear)/(zFar-zNear));
    return result;
}

template<typename T>
Matrix<4, 4, T> PerspectiveMatrix4x4(const T& aspectRatio, const T& fovy, const T& farPlane, const T& nearPlane) {
    Matrix<4, 4, T> result(T(1));
    T f = 1 / std::tan(fovy / T(2));
    result[0][0] = f / aspectRatio;
    result[1][1] = f;
    if(farPlane != std::numeric_limits<T>::infinity()) {
        result[2][2] = (nearPlane + farPlane) / (nearPlane - farPlane);
        result[2][3] = 2 * nearPlane * farPlane / (nearPlane - farPlane);
    } else {
        result[2][2] = -1;
        result[2][3] = -2 * nearPlane;
    }
    result[3][2] = -1;
    result[3][3] = 0;
    return result;
}

template<typename T> //top: nem (0,0,1), hanem meroleges a targetre es dirre
Matrix<4, 4, T> ViewMatrix4x4(const Vector<3, T>& target, const Vector<3, T>& top, const Vector<3, T>& direction, const T& distance) {
    Matrix<4, 4, T> result(T(1));
    Vector<3, T> s = Cross(direction, top);
    result[0][0] = s[0];
    result[0][1] = s[1];
    result[0][2] = s[2];
    result[1][0] = top[0];
    result[1][1] = top[1];
    result[1][2] = top[2];
    result[2][0] = -direction[0];
    result[2][1] = -direction[1];
    result[2][2] = -direction[2];
    return result * TranslationMatrix4x4(distance * direction - target);
}

template<typename T>
Quaternion<T> AxisAngleQuaternion(const Vector<3, T>& axis, const T& angle) {
    T halfAngle = angle / T(2);
    T sinAngle = std::sin(halfAngle);
    return Quaternion<T>(std::cos(halfAngle), axis[0] * sinAngle, axis[1] * sinAngle, axis[2] * sinAngle);
}

template<typename T>
Quaternion<T> Matrix3x3ToQuaternion(const Matrix<3, 3, T>& a) {
    Quaternion<T> result;
    T tr = a[0][0] + a[1][1] + a[2][2];
    if (tr > 0) {
        T s = std::sqrt(tr + 1.0) * 2;
        result[0] = 0.25f * s;
        result[1] = (a[2][1] - a[1][2]) / s;
        result[2] = (a[0][2] - a[2][0]) / s;
        result[3] = (a[1][0] - a[0][1]) / s;
    } else if ((a[0][0] > a[1][1]) && (a[0][0] > a[2][2])) {
        T s = std::sqrt(1.0 + a[0][0] - a[1][1] - a[2][2]) * 2;
        result[0] = (a[2][1] - a[1][2]) / s;
        result[1] = 0.25f * s;
        result[2] = (a[0][1] + a[1][0]) / s;
        result[3] = (a[0][2] + a[2][0]) / s;
    } else if (a[1][1] > a[2][2]) {
        T s = sqrt(1.0 + a[1][1] - a[0][0] - a[2][2]) * 2;
        result[0] = (a[0][2] - a[2][0]) / s;
        result[1] = (a[0][1] + a[1][0]) / s;
        result[2] = 0.25f * s;
        result[3] = (a[1][2] + a[2][1]) / s;
    } else {
        T s = sqrt(1.0 + a[2][2] - a[0][0] - a[1][1]) * 2;
        result[0] = (a[1][0] - a[0][1]) / s;
        result[1] = (a[0][2] + a[2][0]) / s;
        result[2] = (a[1][2] + a[2][1]) / s;
        result[3] = 0.25f * s;
    }
    return result;
}

template<typename T>
Quaternion<T> Matrix4x4ToQuaternion(const Matrix<4, 4, T>& a) {
    Quaternion<T> result;
    T tr = a[0][0] + a[1][1] + a[2][2];
    if (tr > 0) {
        T s = std::sqrt(tr + 1) * 2;
        result[0] = 0.25f * s;
        result[1] = (a[2][1] - a[1][2]) / s;
        result[2] = (a[0][2] - a[2][0]) / s;
        result[3] = (a[1][0] - a[0][1]) / s;
    } else if ((a[0][0] > a[1][1]) && (a[0][0] > a[2][2])) {
        T s = std::sqrt(1 + a[0][0] - a[1][1] - a[2][2]) * 2;
        result[0] = (a[2][1] - a[1][2]) / s;
        result[1] = 0.25f * s;
        result[2] = (a[0][1] + a[1][0]) / s;
        result[3] = (a[0][2] + a[2][0]) / s;
    } else if (a[1][1] > a[2][2]) {
        T s = sqrt(1 + a[1][1] - a[0][0] - a[2][2]) * 2;
        result[0] = (a[0][2] - a[2][0]) / s;
        result[1] = (a[0][1] + a[1][0]) / s;
        result[2] = 0.25f * s;
        result[3] = (a[1][2] + a[2][1]) / s;
    } else {
        T s = sqrt(1 + a[2][2] - a[0][0] - a[1][1]) * 2;
        result[0] = (a[1][0] - a[0][1]) / s;
        result[1] = (a[0][2] + a[2][0]) / s;
        result[2] = (a[1][2] + a[2][1]) / s;
        result[3] = 0.25f * s;
    }
    return result;
}

} // namespace LinAlg

#endif // LINALG_TRANSFORMS_H_INCLUDED
