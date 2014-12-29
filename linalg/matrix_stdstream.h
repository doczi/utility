#ifndef LINALG_MATRIX_STDSTREAM_H_INCLUDED
#define LINALG_MATRIX_STDSTREAM_H_INCLUDED

#include <iostream>
#include "matrix.h"

namespace LinAlg {

// Interface //

template<unsigned n, unsigned m, typename T>
std::ostream& operator<<(std::ostream& a, const Matrix<n, m, T>& b);
template<unsigned n, unsigned m, typename T>
std::istream& operator>>(std::istream& a, Matrix<n, m, T>& b);



// Implementation //

template<unsigned n, unsigned m, typename T>
std::ostream& operator<<(std::ostream& a, const Matrix<n, m, T>& b) {
    for (unsigned i = 0; i < Matrix<n, m, T>::rows; ++i){
        for (unsigned j = 0; j < Matrix<n, m, T>::columns; ++j){
            a << " " << b[i][j];
        }
        a << std::endl;
    }
    return a;
}

} // namespace LinAlg

#endif // LINALG_MATRIX_STDSTREAM_H_INCLUDED
