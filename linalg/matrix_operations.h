#ifndef LINALG_MATRIX_OPERATIONS_H_INCLUDED
#define LINALG_MATRIX_OPERATIONS_H_INCLUDED

#include "matrix.h"
#include "operations.h"

#include "matrix_stdstream.h"

namespace LinAlg {

// Interface //

template<typename T, unsigned n, unsigned l, unsigned m>
Matrix<n, m, T> operator*(const Matrix<n, l, T>& a, const Matrix<l, m, T>& b); // ordinary matrix multiplication
template<unsigned n, typename T> Matrix<n, n, T>& operator*=(Matrix<n, n, T>& a, const Matrix<n, n, T>& b); // ordinary matrix multiplication
template<unsigned n, unsigned m, typename T> Matrix<m, n, T> Transpose(const Matrix<n, m, T>& a);
template<unsigned n, unsigned m, typename T> Matrix<n, m, T> GaussJordanElimanation(const Matrix<n, m, T>& a);
template<unsigned n, typename T> Matrix<n, n, T> Inverse(const Matrix<n, n, T>& a);
template<unsigned n, typename T> Matrix<n, n, T> FastInverse(const Matrix<n, n, T>& a); // top-left: rotation; top-right: translation
template<unsigned n, typename T> Matrix<n, n, T> FastInverse2(const Matrix<n, n, T>& a); // top-left: rotation; bottom-left: translation
template<unsigned n, typename T> T Determinant(const Matrix<n, n, T>& a); // missing implementation



// Implementation //

template<typename T, unsigned n, unsigned l, unsigned m>
Matrix<n, m, T> operator*(const Matrix<n, l, T>& a, const Matrix<l, m, T>& b) {
    if(l == 0) return Matrix<n, m, T>(T(0));
    Matrix<n, m, T> result;
    for(unsigned i = 0; i < n; ++i){
        for(unsigned j = 0; j < m; ++j){
            result[i][j] = a[i][0] * b[0][j];
            for(unsigned k = 1; k < l; ++k){
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

template<unsigned n, typename T>
Matrix<n, n, T>& operator*=(const Matrix<n, n, T>& a, const Matrix<n, n, T>& b) {
    return a = a * b;
}

template<unsigned n, unsigned m, typename T>
Matrix<m, n, T> Transpose(const Matrix<n, m, T>& a){
    Matrix<m, n, T> result;
    for(unsigned i = 0; i < n; ++i){
        for(unsigned j = 0; j < m; ++j){
            result[j][i] = a[i][j];
        }
    }
    return result;
}

template<unsigned n, unsigned m, typename T>
Matrix<n, m, T> GaussJordanElimination(const Matrix<n, m, T>& a){
    Matrix<n, m, T> result = a;
    unsigned i = 0;
    unsigned j = 0;
    while((i < n) && (j < m)) {
        unsigned maxi = i;
        for(unsigned k = i + 1; k < n; ++k) {
            if(std::fabs(result[k][j]) > std::fabs(result[maxi][j])) {
                maxi = k;
            }
        }
        T t = result[maxi][j];
        if(std::fabs(t) > EPSILON) {
            for(unsigned k = 0; k < m; ++k){
                T s = result[maxi][k];
                result[maxi][k] = result[i][k];
                result[i][k] = s / t;
            }
            for(unsigned u = i + 1; u < n; ++u){
                T t = result[u][j];
                for(unsigned k = 0; k < m; ++k){
                    result[u][k] -= t * result[i][k];
                }
            }
            ++i;
        }
        ++j;
    }
    for(unsigned i = n - 1; i > 0; --i){
        for(unsigned j = 0; j < i; ++j){
            T t = result[j][i];
            for(unsigned k = i; k < m; ++k){
                result[j][k] -= t * result[i][k];
            }
        }
    }
    return result;
}

template<unsigned n, typename T>
Matrix<n, n, T> Inverse(const Matrix<n, n, T>& a) {
    Matrix<n, 2*n, T> temp;
    Matrix<n, n, T> result;
    for(unsigned i = 0; i < n; ++i){
        for(unsigned j = 0; j < n; ++j){
            temp[i][j] = a[i][j];
            temp[i][j + n] = 0;
        }
        temp[i][i + n] = 1;
    }
    temp = GaussJordanElimination(temp);
    for(unsigned i = 0; i < n; ++i){
        for(unsigned j = 0; j < n; ++j){
            result[i][j] = temp[i][j + n];
        }
    }
    return result;
}

template<unsigned n, typename T>
Matrix<n, n, T> FastInverse(const Matrix<n, n, T>& a) {
    Matrix<n, n, T> result;
    for(unsigned i = 0; i < n-1; ++i){
        T sum = T(0);
        for(unsigned j = 0; j < n-1; ++j){
            result[i][j] = a[j][i];
            sum -= a[j][i] * a[j][n-1];
        }
        result[i][n-1] = sum;
        result[n-1][i] = T(0);
    }
    result[n-1][n-1] = T(1);
    return result;
}

template<unsigned n, typename T>
Matrix<n, n, T> FastInverse2(const Matrix<n, n, T>& a) {
    Matrix<n, n, T> result;
    for(unsigned i = 0; i < n-1; ++i){
        T sum = T(0);
        for(unsigned j = 0; j < n-1; ++j){
            result[j][i] = a[i][j];
            sum -= a[i][j] * a[n-1][j];
        }
        result[n-1][i] = sum;
        result[i][n-1] = T(0);
    }
    result[n-1][n-1] = T(1);
    return result;
}

/*
template<unsigned n, unsigned m, typename T>
Matrix<n, m, T> HadamardProduct(const Matrix<n, m, T>& a, const Matrix<n, m, T>& b) {
    Matrix<n, m, T> result;
    for(unsigned i = 0; i < Matrix<n, m, T>::dimensions; ++i){
        result.data[i] = a.data[i] * b.data[i];
    }
    return result;
}

template<typename T, unsigned n, unsigned m, unsigned l, unsigned k>
Matrix<T, n*l, m*k> KroneckerProduct(const Matrix<n, m, T>& a, const Matrix<T, l, k>& b){
    Matrix<T, n*l, m*k> result;
    for(unsigned g = 0; g < n; ++g){
        for(unsigned h = 0; h < m; ++h){
            for(unsigned i = 0; i < l; ++i){
                for(unsigned j = 0; j < k; ++j){
                    result[n*g + i][m*h + j] = a[g][h] * b[i][j];
                }
            }
        }
    }
    return result;
}
*/

} // namespace LinAlg

#endif // LINALG_MATRIX_OPERATIONS_H_INCLUDED
