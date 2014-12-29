#ifndef LINALG_VECTOR_STDSTREAM_H_INCLUDED
#define LINALG_VECTOR_STDSTREAM_H_INCLUDED

#include <iostream>
#include "vector.h"

namespace LinAlg {

// Interface //

template<unsigned n, typename T> std::ostream& operator<<(std::ostream& a, const Vector<n, T>& b);
template<unsigned n, typename T> std::istream& operator>>(std::istream& a, const Vector<n, T>& b);



// Implementation //

template<unsigned n, typename T>
std::ostream& operator<<(std::ostream& a, const Vector<n, T>& b) {
    if (Vector<n, T>::dimensions == 0) return a << "()";
    a << "(" << b.data[0];
    for (unsigned i = 1; i < Vector<n, T>::dimensions; ++i){
        a << ";" << b.data[i];
    }
    return a << ")";
}

}

#endif // LINALG_VECTOR_STDSTREAM_H_INCLUDED
