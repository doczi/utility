#ifndef LINALG_QUATERNION_QTSTREAM_H_INCLUDED
#define LINALG_QUATERNION_QTSTREAM_H_INCLUDED

#include <QTextStream>
#include <QDataStream>

namespace LinAlg {

// Interface //

template<typename T> QTextStream& operator<<(QTextStream& a, const Quaternion<T>& b);
template<typename T> QTextStream& operator>>(QTextStream& a, Quaternion<T>& b);
template<typename T> QDataStream& operator<<(QDataStream& a, const Quaternion<T>& b);
template<typename T> QDataStream& operator>>(QDataStream& a, Quaternion<T>& b);



// Implementation //

template<typename T>
QTextStream& operator<<(QTextStream& a, const Quaternion<T>& b) {
    a << "(" << b.data[0];
    for (unsigned i = 1; i < Quaternion<T>::dimensions; ++i){
        a << ";" << b.data[i];
    }
    return a << ")";
}

template<typename T>
QDataStream& operator<<(QDataStream& a, const Quaternion<T>& b) {
    for (unsigned i = 0; i < Quaternion<T>::dimensions; ++i){
        a << b.data[i];
    }
    return a;
}

template<typename T>
QDataStream& operator>>(QDataStream& a, const Quaternion<T>& b) {
    for (unsigned i = 0; i < Quaternion<T>::dimensions; ++i){
        a >> b.data[i];
    }
    return a;
}

} // namespace LinAlg

#endif // LINALG_QUATERNION_QTSTREAM_H_INCLUDED
