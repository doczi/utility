#ifndef LINALG_QUATERNION_STDSTREAM_H_INCLUDED
#define LINALG_QUATERNION_STDSTREAM_H_INCLUDED

#include <iostream>
#include "quaternion.h"

namespace LinAlg {

// Interface //

template<typename T> std::ostream& operator<<(std::ostream& a, const Quaternion<T>& b);
template<typename T> std::istream& operator>>(std::istream& a, const Quaternion<T>& b);



// Implementation //

template<typename T>
std::ostream& operator<<(std::ostream& a, const Quaternion<T>& b) {
    a << "(" << b.data[0];
    for (unsigned i = 1; i < Quaternion<T>::dimensions; ++i){
        a << "; " << b.data[i];
    }
    return a << ")";
}

}

#endif // LINALG_QUATERNION_STDSTREAM_H_INCLUDED
