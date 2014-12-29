#ifndef LINALG_QUATERNION_OPERATIONS_H_INCLUDED
#define LINALG_QUATERNION_OPERATIONS_H_INCLUDED

#include "quaternion.h"
#include "operations.h"

namespace LinAlg {

// Interface //

template<typename T> Quaternion<T> operator*(const Quaternion<T>& a, const Quaternion<T>& b); // ordinary quaternion multiplication
template<typename T> Quaternion<T> Conjugate(const Quaternion<T>& a);
template<typename T> Quaternion<T> Inverse(const Quaternion<T>& a);
template<typename T> Quaternion<T> Slerp(const Quaternion<T>& a, const Quaternion<T>& b, const T& t);
template<typename T> T Angle(const Quaternion<T>& a, const Quaternion<T>& b);



// Implementation //

template<typename T>
inline Quaternion<T> operator*(const Quaternion<T>& a, const Quaternion<T>& b) {
    Quaternion<T> result;
    result[0] = a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3];
    result[1] = a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2];
    result[2] = a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1];
    result[3] = a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0];
    return result;
}

template<typename T>
inline Quaternion<T> Conjugate(const Quaternion<T>& a) {
    Quaternion<T> result;
    result[0] =  a[0];
    result[1] = -a[1];
    result[2] = -a[2];
    result[3] = -a[3];
    return result;
}

template<typename T>
inline Quaternion<T> Inverse(const Quaternion<T>& a) {
    return Conjugate(a) / SquareLength(a);
}

template<typename T>
inline Quaternion<T> Slerp(const Quaternion<T>& a, const Quaternion<T>& b, const T& t) {
	T cosTheta = Dot(a, b) / std::sqrt(SquareLength(a) * SquareLength(b));
	T theta = std::acos(cosTheta);
	T sinTheta = std::sin(theta);
	if(std::fabs(sinTheta) < EPSILON) return a;
	T s = (cosTheta < 0) ? (1 - t) : (t - 1);
	return a*(std::sin(s*theta) / sinTheta) + b*(std::sin(t*theta) / sinTheta);
}

template<typename T>
inline T Angle(const Quaternion<T>& a, const Quaternion<T>& b) {
    return 2*std::acos(Dot(a, b) / std::sqrt(SquareLength(a) * SquareLength(b)));
}

} // namespace LinAlg

#endif // LINALG_QUATERNION_OPERATIONS_H_INCLUDED
