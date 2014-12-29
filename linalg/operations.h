#ifndef LINALG_OPERATIONS_H_INCLUDED
#define LINALG_OPERATIONS_H_INCLUDED

#include <cmath>
#include <limits>

namespace LinAlg{

// Interface //

const double PI = 3.1415926535897932;
const double E = 2.7182818284590452;
const double RAD = 180.0 / PI;
const double EPSILON = 1E-4;
//template<typename V> bool operator==(const V& a, const V& b);
//template<typename V> bool operator!=(const V& a, const V& b);
template<typename V> V operator+(const V& a);
template<typename V> V operator-(const V& a);
template<typename V> V operator+(const V& a, const V& b);
template<typename V> V& operator+=(V& a, const V& b);
template<typename V> V operator-(const V& a, const V& b);
template<typename V> V& operator-=(V& a, const V& b);
template<typename V> V operator*(const V& a, const typename V::ComponentType& b);
template<typename V> V& operator*=(V& a, const typename V::ComponentType& b);
template<typename V> V operator/(const V& a, const typename V::ComponentType& b);
template<typename V> V& operator/=(V& a, const typename V::ComponentType& b);
template<typename V> V operator*(const typename V::ComponentType& a, const V& b);
template<typename V> typename V::ComponentType Dot(const V& a, const V& b);
template<typename V> typename V::ComponentType SquareLength(const V& a);
template<typename V> typename V::ComponentType Length(const V& a);
template<typename V> V Normalize(const V& a);
template<typename V> V Lerp(const V& a, const V& b, const typename V::ComponentType& t);
template<typename V> V Nlerp(const V& a, const V& b, const typename V::ComponentType& t);



// Implementation //
/*
template<typename V>
inline bool operator==(const V& a, const V& b) {
    for(unsigned i = 0; i < V::dimensions; ++i) {
        if(a.data[i] != b.data[i]) return false;
    }
    return true;
}

template<typename V>
inline bool operator!=(const V& a, const V& b) {
    for(unsigned i = 0; i < V::dimensions; ++i) {
        if(a.data[i] != b.data[i]) return true;
    }
    return false;
}
*/
template<typename V>
inline V operator+(const V& a) {
    return a;
}

template<typename V>
inline V operator-(const V& a) {
    V result;
    for(unsigned i = 0; i < V::dimensions; ++i){
        result.data[i] = -a.data[i];
    }
    return result;
}

template<typename V>
inline V operator+(const V& a, const V& b) {
    V result;
    for(unsigned i = 0; i < V::dimensions; ++i){
        result.data[i] = a.data[i] + b.data[i];
    }
    return result;
}

template<typename V>
inline V& operator+=(V& a, const V& b) {
    for(unsigned i = 0; i < V::dimensions; ++i){
        a.data[i] += b.data[i];
    }
    return a;
}

template<typename V>
inline V operator-(const V& a, const V& b) {
    V result;
    for(unsigned i = 0; i < V::dimensions; ++i){
        result.data[i] = a.data[i] - b.data[i];
    }
    return result;
}

template<typename V>
inline V& operator-=(V& a, const V& b) {
    for(unsigned i = 0; i < V::dimensions; ++i){
        a.data[i] -= b.data[i];
    }
    return a;
}

template<typename V>
inline V operator*(const V& a, const typename V::ComponentType& b) {
    V result;
    for(unsigned i = 0; i < V::dimensions; ++i){
        result.data[i] = a.data[i] * b;
    }
    return result;
}

template<typename V>
inline V& operator*=(V& a, const typename V::ComponentType& b) {
    for(unsigned i = 0; i < V::dimensions; ++i){
        a.data[i] *= b;
    }
    return a;
}

template<typename V>
inline V operator/(const V& a, const typename V::ComponentType& b) {
    V result;
    for(unsigned i = 0; i < V::dimensions; ++i){
        result.data[i] = a.data[i] / b;
    }
    return result;
}

template<typename V>
inline V& operator/=(V& a, const typename V::ComponentType& b) {
    for(unsigned i = 0; i < V::dimensions; ++i){
        a.data[i] /= b;
    }
    return a;
}

template<typename V>
inline V operator*(const typename V::ComponentType& a, const V& b) {
    V result;
    for(unsigned i = 0; i < V::dimensions; ++i){
        result.data[i] = a * b.data[i];
    }
    return result;
}

template<typename V>
inline typename V::ComponentType Dot(const V& a, const V& b) {
    if(V::dimensions == 0) return 0;
    typename V::ComponentType result = a.data[0] * b.data[0];
    for(unsigned i = 1; i < V::dimensions; ++i){
        result += a.data[i] * b.data[i];
    }
    return result;
}

template<typename V>
inline typename V::ComponentType SquareLength(const V& a) {
    return Dot(a, a);
}

template<typename V>
inline typename V::ComponentType Length(const V& a) {
    return std::sqrt(Dot(a, a));
}

template<typename V>
inline V Normalize(const V& a) {
    return a / std::sqrt(Dot(a, a));
}

template<typename V>
inline V Lerp(const V& a, const V& b, const typename V::ComponentType& t) {
    return (1-t)*a + t*b;
}

template<typename V>
inline V Nlerp(const V& a, const V& b, const typename V::ComponentType& t) {
    return Normalize((1-t)*a + t*b);
}

} // namespace LinAlg

#endif // LINALG_OPERATIONS_H_INCLUDED
