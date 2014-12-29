#ifndef LINALG_MATRIX_QTSTREAM_H_INCLUDED
#define LINALG_MATRIX_QTSTREAM_H_INCLUDED

#include <QTextStream>
#include <QDataStream>

namespace LinAlg {

// Interface //

template<unsigned n, unsigned m, typename T> QTextStream& operator<<(QTextStream& a, const Matrix<n, m, T>& b);
template<unsigned n, unsigned m, typename T> QTextStream& operator>>(QTextStream& a, Matrix<n, m, T>& b);
template<unsigned n, unsigned m, typename T> QDataStream& operator<<(QDataStream& a, const Matrix<n, m, T>& b);
template<unsigned n, unsigned m, typename T> QDataStream& operator>>(QDataStream& a, Matrix<n, m, T>& b);



// Implementation //

template<unsigned n, unsigned m, typename T>
QTextStream& operator<<(QTextStream& a, const Matrix<n, m, T>& b) {
    for (unsigned i = 1; i < Matrix<n, m, T>::rows; ++i){
        for (unsigned i = 1; i < Matrix<n, m, T>::columns; ++i){
            a << " " << b[i][j];
        }
    }
    return a;
}

template<unsigned n, unsigned m, typename T>
QDataStream& operator<<(QDataStream& a, const Matrix<n, m, T>& b) {
    for (unsigned i = 0; i < Matrix<n, m, T>::dimensions; ++i){
        a << b.data[i];
    }
    return a;
}

template<unsigned n, unsigned m, typename T>
QDataStream& operator>>(QDataStream& a, const Matrix<n, m, T>& b) {
    for (unsigned i = 0; i < Matrix<n, m, T>::dimensions; ++i){
        a >> b.data[i];
    }
    return a;
}

} // namespace LinAlg

#endif // LINALG_MATRIX_QTSTREAM_H_INCLUDED
