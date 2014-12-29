#ifndef LINALG_VECTOR_OPERATIONS_H_INCLUDED
#define LINALG_VECTOR_OPERATIONS_H_INCLUDED

#include "vector.h"
#include "operations.h"

namespace LinAlg {

// Interface //

template<unsigned n, typename T> Vector<n, T> operator*(const Vector<n, T>& a, const Vector<n, T>& b); // component-wise, not dot or cross !!!
template<unsigned n, typename T> Vector<n, T>& operator*=(Vector<n, T>& a, const Vector<n, T>& b); // component-wise, not dot or cross !!!
template<unsigned n, typename T> Vector<n, T> operator/(const Vector<n, T>& a, const Vector<n, T>& b);
template<unsigned n, typename T> Vector<n, T>& operator/=(Vector<n, T>& a, const Vector<n, T>& b);
template<unsigned n, typename T> T SquareDistance(const Vector<n, T>& a, const Vector<n, T>& b);
template<unsigned n, typename T> T Distance(const Vector<n, T>& a, const Vector<n, T>& b);
template<unsigned n, typename T> T Angle(const Vector<n, T>& a, const Vector<n, T>& b);
template<unsigned n, typename T> Vector<n, T> AngleBisector(const Vector<n, T>& a, const Vector<n, T>& b);
template<unsigned n, typename T> Vector<n, T> Project(const Vector<n, T>& incident, const Vector<n, T>& tangent);
template<unsigned n, typename T> Vector<n, T> Reflect(const Vector<n, T>& incident, const Vector<n, T>& normal);
template<unsigned n, typename T> Vector<n, T> Refract(const Vector<n, T>& incident, const Vector<n, T>& normal, const T& indexOfRefraction);
template<unsigned n, typename T> Vector<n, T> Slerp(const Vector<n, T>& a, const Vector<n, T>& b, const T& t);
template<unsigned n, typename T> Vector<n-1, T> HomogeneousDivide(const Vector<n, T>& a);
template<unsigned n, typename T> Vector<n+1, T> MakeHomogeneous(const Vector<n, T>& a, const T& b = T(1));
template<typename T> T Angle2(const Vector<2, T>& a, const Vector<2, T>& b);
template<typename T> T PerpDot(const Vector<2, T>& a, const Vector<2, T>& b);
template<typename T> Vector<2, T> Perpendicular(const Vector<2, T>& a);
template<unsigned n, typename T> Vector<2, T> Barycentric(const Vector<n, T> vector, const Vector<n, T>& baseA, const Vector<n, T> baseB);
template<typename T> Vector<3, T> Cross(const Vector<3, T>& a, const Vector<3, T>& b);



// Impementation //

template<unsigned n, typename T>
inline Vector<n, T> operator*(const Vector<n, T>& a, const Vector<n, T>& b) {
    Vector<n, T> result;
    for(unsigned i = 0; i < n; ++i){
        result[i] = a[i] * b[i];
    }
    return result;
}

template<unsigned n, typename T>
inline Vector<n, T>& operator*=(Vector<n, T>& a, const Vector<n, T>& b) {
    for(unsigned i = 0; i < n; ++i){
        a[i] *= b[i];
    }
    return a;
}

template<unsigned n, typename T>
inline Vector<n, T> operator/(const Vector<n, T>& a, const Vector<n, T>& b) {
    Vector<n, T> result;
    for(unsigned i = 0; i < n; ++i){
        result[i] = a[i] / b[i];
    }
    return result;
}

template<unsigned n, typename T>
inline Vector<n, T>& operator/=(Vector<n, T>& a, const Vector<n, T>& b) {
    for(unsigned i = 0; i < n; ++i){
        a[i] /= b[i];
    }
    return a;
}

template<unsigned n, typename T>
inline T SquareDistance(const Vector<n, T>& a, const Vector<n, T>& b) {
    return SquareLength(a - b);
}

template<unsigned n, typename T>
inline T Distance(const Vector<n, T>& a, const Vector<n, T>& b) {
    return Length(a - b);
}

template<unsigned n, typename T>
inline T Angle(const Vector<n, T>& a, const Vector<n, T>& b) {
    return std::acos(Dot(a, b) / std::sqrt(SquareLength(a) * SquareLength(b)));
}

template<unsigned n, typename T>
inline Vector<n, T> AngleBisector(const Vector<n, T>& a, const Vector<n, T>& b) {
    return (Normalize(a) + Normalize(b)) / 2;
}

template<unsigned n, typename T>
inline Vector<n, T> Project(const Vector<n, T>& incident, const Vector<n, T>& tangent) {
    return tangent * (Dot(incident, tangent) / Dot(tangent, tangent));
}

template<unsigned n, typename T>
inline Vector<n, T> Reflect(const Vector<n, T>& incident, const Vector<n, T>& normal) {
    Vector<n, T> nn = Normalize(normal);
    return incident - Dot(incident, nn)*2*nn;
}

template<unsigned n, typename T>
inline Vector<n, T> Refract(const Vector<n, T>& incident, const Vector<n, T>& normal, const T& ior) {
    Vector<n, T> nn = Normalize(normal);
    T dot = Dot(incident, nn);
    T k = 1 - ior*ior * (1 - dot*dot);
    return (k >= 0) ? (ior*incident - (ior + std::sqrt(k))*nn) : (incident - 2*dot*nn);
}

template<unsigned n, typename T>
inline Vector<n, T> Slerp(const Vector<n, T>& a, const Vector<n, T>& b, const T& t) {
    T theta = Angle(a, b);
    if(theta < EPSILON) {
        return a;
    } else {
        return (a * std::sin((1-t) * theta) + b * std::sin(t * theta)) / std::sin(theta);
    }
}

template<unsigned n, typename T>
inline Vector<n-1, T> HomogeneousDivide(const Vector<n, T>& a) {
    Vector<n-1, T> result;
    for(unsigned i = 0; i < n-1; ++i) {
        result[i] = a[i] / a[n-1];
    }
    return result;
}

template<unsigned n, typename T>
inline Vector<n+1, T> MakeHomogeneous(const Vector<n, T>& a, const T& b) {
    Vector<n+1, T> result;
    for(unsigned i = 0; i < n; ++i) {
        result[i] = a[i];
    }
    result[n] = b;
    return result;
}

template<typename T>
inline T Angle2(const Vector<2, T>& a, const Vector<2, T>& b) {
    return std::atan2(b[1], b[0]) - std::atan2(a[1], a[0]);
}

template<typename T>
inline T PerpDot(const Vector<2, T>& a, const Vector<2, T>& b) {
    return Dot(Perpendicular(a), b);
}

template<typename T>
inline Vector<2, T> Perpendicular(const Vector<2, T>& a) {
    return Vector<2, T>(-a[1], a[0]);
}

template<unsigned n, typename T>
inline Vector<2, T> Barycentric(const Vector<n, T> vector, const Vector<n, T>& baseA, const Vector<n, T> baseB) {
    T dotAA = Dot(baseA, baseA);
    T dotAB = Dot(baseA, baseB);
    T dotAV = Dot(baseA, vector);
    T dotBB = Dot(baseB, baseB);
    T dotBV = Dot(baseB, vector);
    T denominator = dotAA * dotBB - dotAB * dotAB;
    return Vector<2, T>((dotBB * dotAV - dotAB * dotBV) / denominator,
                        (dotAA * dotBV - dotAB * dotAV) / denominator);
}

template<typename T>
inline Vector<3, T> Cross(const Vector<3, T>& a, const Vector<3, T>& b) {
    Vector<3, T> result;
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
    return result;
}

} // namespace LinAlg

#endif // LINALG_VECTOR_OPERATIONS_H_INCLUDED
