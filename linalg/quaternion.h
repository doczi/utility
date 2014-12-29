#ifndef LINALG_QUATERNION_H_INCLUDED
#define LINALG_QUATERNION_H_INCLUDED

namespace LinAlg {

// Interface //

template<typename T>
class Quaternion{
public:
    typedef T ComponentType;
    static const unsigned dimensions = 4;
    T data[dimensions];
    Quaternion(const T& r = T(1));
    Quaternion(const T& r, const T& i, const T& j, const T& k);
    Quaternion(const T* a);
    const T& operator[](unsigned index) const;
    T& operator[](unsigned index);
};



// Implementation //

template<typename T>
inline Quaternion<T>::Quaternion(const T& r) {
    data[0] = r;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
}

template<typename T>
inline Quaternion<T>::Quaternion(const T* a) {
    for(unsigned i = 0; i < dimensions; ++i) {
        data[i] = a[i];
    }
}

template<typename T>
inline Quaternion<T>::Quaternion(const T& r, const T& i, const T& j, const T& k) {
    data[0] = r;
    data[1] = i;
    data[2] = j;
    data[3] = k;
}

template<typename T>
inline const T& Quaternion<T>::operator[](unsigned index) const {
    return data[index];
}

template<typename T>
inline T& Quaternion<T>::operator[](unsigned index) {
    return data[index];
}

} // namespace LinAlg

#endif // LINALG_QUATERNION_H_INCLUDED
