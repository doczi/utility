#ifndef LINALG_MATRIX_H_INCLUDED
#define LINALG_MATRIX_H_INCLUDED

namespace LinAlg {

// Interface //

template<unsigned n, unsigned m, typename T>
class Matrix{
public:
    typedef T ComponentType;
    static const unsigned dimensions = n * m;
    static const unsigned rows = n;
    static const unsigned columns = m;
    T data[dimensions];
    Matrix(const T& a = T(1));
    Matrix(const T* a);
    const T* operator[](unsigned index) const;
    T* operator[](unsigned index);
};



// Implementation //

template<unsigned n, unsigned m, typename T>
inline Matrix<n, m, T>::Matrix(const T* a) {
    for(unsigned i = 0; i < dimensions; ++i) {
        data[i] = a[i];
    }
}

template<unsigned n, unsigned m, typename T>
inline Matrix<n, m, T>::Matrix(const T& a) {
    for(unsigned i = 0; i < dimensions; ++i) {
        data[i] = 0;
    }
    for(unsigned i = 0; (i < n) && (i < m); ++i) {
        data[i * n + i] = a;
    }
}

template<unsigned n, unsigned m, typename T>
inline const T* Matrix<n, m, T>::operator[](unsigned index) const {
    return data + index * m;
}

template<unsigned n, unsigned m, typename T>
inline T* Matrix<n, m, T>::operator[](unsigned index) {
    return data + index * m;
}

} // namespace LinAlg

#endif // LINALG_MATRIX_H_INCLUDED
