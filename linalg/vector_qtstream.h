#ifndef LINALG_VECTOR_QTSTREAM_INCLUDED
#define LINALG_VECTOR_QTSTREAM_INCLUDED

#include <QTextStream>
#include <QDataStream>

namespace LinAlg {

// Interface //

template<unsigned n, typename T> QTextStream& operator<<(QTextStream& a, const Vector<n, T>& b);
template<unsigned n, typename T> QTextStream& operator>>(QTextStream& a, Vector<n, T>& b);
template<unsigned n, typename T> QDataStream& operator<<(QDataStream& a, const Vector<n, T>& b);
template<unsigned n, typename T> QDataStream& operator>>(QDataStream& a, Vector<n, T>& b);



// Implementation //

template<unsigned n, typename T>
QTextStream& operator<<(QTextStream& a, const Vector<n, T>& b) {
    if (Vector<n, T>::dimensions == 0){
        return a << "()";
    }
    a << "(" << b.data[0];
    for (unsigned i = 1; i < Vector<n, T>::dimensions; ++i){
        a << ";" << b.data[i];
    }
    return a << ")";
}

template<unsigned n, typename T>
QDataStream& operator<<(QDataStream& a, const Vector<n, T>& b) {
    for (unsigned i = 0; i < Vector<n, T>::dimensions; ++i){
        a << b.data[i];
    }
    return a;
}

template<unsigned n, typename T>
QDataStream& operator>>(QDataStream& a, const Vector<n, T>& b) {
    for (unsigned i = 0; i < Vector<n, T>::dimensions; ++i){
        a >> b.data[i];
    }
    return a;
}

} // namespace LinAlg

#endif // LINALG_VECTOR_QTSTREAM_INCLUDED
