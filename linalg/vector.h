#ifndef LINALG_VECTOR_H_INCLUDED
#define LINALG_VECTOR_H_INCLUDED

namespace LinAlg {

template<unsigned n, typename T>
class Vector{
public:
    typedef T ComponentType;
    static const unsigned dimensions = n;
    T data[dimensions];
    inline Vector(const T& a = T(0)) {for(unsigned i = 0; i < dimensions; data[i++] = a);}
    inline Vector(const T* a) {for(unsigned i = 0; i < dimensions; ++i) data[i] = a[i];}
    inline const T& operator[](unsigned index) const {return data[index];}
    inline T& operator[](unsigned index) {return data[index];}
};

template<typename T>
class Vector<2, T>{
public:
    typedef T ComponentType;
    static const unsigned dimensions = 2;
    T data[dimensions];
    inline Vector(const T& a = T(0)) {for(unsigned i = 0; i < dimensions; data[i++] = a);}
    inline Vector(const T& x, const T& y) {data[0] = x; data[1] = y;}
    inline Vector(const T* a) {for(unsigned i = 0; i < dimensions; ++i) data[i] = a[i];}
    inline const T& operator[](unsigned index) const {return data[index];}
    inline T& operator[](unsigned index) {return data[index];}
};

template<typename T>
class Vector<3, T>{
public:
    typedef T ComponentType;
    static const unsigned dimensions = 3;
    T data[dimensions];
    inline Vector(const T& a = T(0)) {for(unsigned i = 0; i < dimensions; data[i++] = a);}
    inline Vector(const T& x, const T& y, const T& z) {data[0] = x; data[1] = y; data[2] = z;}
    inline Vector(const T* a) {for(unsigned i = 0; i < dimensions; ++i) data[i] = a[i];}
    inline const T& operator[](unsigned index) const {return data[index];}
    inline T& operator[](unsigned index) {return data[index];}
};

template<typename T>
class Vector<4, T>{
public:
    typedef T ComponentType;
    static const unsigned dimensions = 4;
    T data[dimensions];
    inline Vector(const T& a = T(0)) {for(unsigned i = 0; i < dimensions; data[i++] = a);}
    inline Vector(const T& x, const T& y, const T& z, const T& w) {data[0] = x; data[1] = y; data[2] = z; data[3] = w;}
    inline Vector(const T* a) {for(unsigned i = 0; i < dimensions; ++i) data[i] = a[i];}
    inline const T& operator[](unsigned index) const {return data[index];}
    inline T& operator[](unsigned index) {return data[index];}
};

} // namespace LinAlg

#endif // LINALG_VECTOR_H_INCLUDED
