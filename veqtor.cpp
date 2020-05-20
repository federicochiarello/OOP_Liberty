#include "veqtor.h"

template<class T>
veqtor<T>::veqtor() : _size(0), _capacity(0), _pointer(nullptr) {}

template<class T>
veqtor<T>::veqtor(unsigned short s, const T& x) : _pointer(s==0 ? nullptr : new T[s]), _size(s), _capacity(s) {
    for(int i = 0; i < _size; ++i) _pointer[i] = x;
}

template<class T>
veqtor<T>::veqtor(const veqtor<T>& v) : _pointer(v.size() == 0 ? nullptr : new T[v.capacity()]),
    _capacity(v.capacity()), _size(v.size()) {
    for(int i = 0; i < _size; ++i) _pointer[i] = v._pointer[i];
}

template<class T>
veqtor<T>::~veqtor() {
    delete[] _pointer;
}

template<class T>
veqtor<T>& veqtor<T>::operator=(const veqtor<T> & v) {
    if(this != &v) {
          delete[] _pointer;
          _pointer = v.size() == 0 ? nullptr : new int[v.capacity()];
          _size = v.size();
          _capacity = v.capacity();
          for(int i = 0; i <_size ; ++i) _pointer[i] = v._pointer[i];
        }
        return *this;
}

template<class T>
void veqtor<T>::expand() {
    _capacity = (_capacity == 0 ? 1 : 2 * _capacity);

    T* tmp = new T[_capacity];
    for (int i = 0; i < _size; i++)
        tmp[i] = _pointer[i];

    delete[] _pointer;
    _pointer = tmp;
}

template<class T>
unsigned short veqtor<T>::capacity() const { return _capacity; }

template<class T>
unsigned short veqtor<T>::size() const { return _size; }

template<class T>
bool veqtor<T>::empty() const { return _size == 0; }

template<class T>
void veqtor<T>::pushBack(const T & x) {
    if (_size == _capacity)  expand();
    _pointer[_size++] = x;
}
