#include "veqtor.h"

template<class T>
veqtor<T>::veqtor() : _size(0), _capacity(0), _pointer(nullptr) {}

template<class T>
veqtor<T>::veqtor(unsigned short s) : _pointer(s==0 ? nullptr : new T[s]), _size(s), _capacity(s) {}

template<class T>
veqtor<T>::veqtor(unsigned short s, const T& x) : _pointer(s==0 ? nullptr : new T[s]), _size(s), _capacity(s) {
    for(int i = 0; i < _size; ++i) _pointer[i] = x;
}

template<class T>
veqtor<T>::veqtor(const veqtor<T>::iterator& it1, const veqtor<T>::iterator& it2) : _pointer(it1.v->size() == 0 ? nullptr : new T[it1.v->size()]),
    _size(it1.v->size()), _capacity(it1.v->size()) {
    for(veqtor<T>::iterator i = it1; i < it2; ++i) _pointer[i] = it1.v->_pointer[i];
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
void veqtor<T>::push_back(const T & x) {
    if (_size == _capacity)  expand();
    _pointer[_size++] = x;
}

template<class T>
void veqtor<T>::pop_back() { _size--; }
//c.erase(--c.end())

template<class T>
T& veqtor<T>::operator[](unsigned int i) const {
    return _pointer[i];
}

template<class T>
T &veqtor<T>::front() const {
    return _pointer[0];
}

template<class T>
T &veqtor<T>::back() const {
    return _pointer[_size - 1];
}

template<class T>
typename veqtor<T>::iterator veqtor<T>::begin() const {
    iterator aux;
    aux.v = this;
    aux.i = 0;
    return aux;
}

template<class T>
typename veqtor<T>::iterator veqtor<T>::end() const {
    iterator aux;
    aux.v = this;
    aux.i = size();
    return aux;
}

template<class T>
void veqtor<T>::insert(veqtor<T>::iterator it, const int& n, const T& x) {
    while (_size + n > _capacity) expand();
    for(veqtor<T>::iterator i = end() + n - 1; i != it + n - 1; --i)  *i = *(i - n);
    for(veqtor<T>::iterator i = it; i != it + n; ++i)  *i = x;
    _size += n;
}

template<class T>
typename veqtor<T>::iterator veqtor<T>::insert(veqtor<T>::iterator it, const T& x) {
    if (_size == _capacity) expand();
    for(veqtor<T>::iterator i = end(); i != it; --i)  *i = *(i - 1);
    *it = x;
    _size++;
    return it;
}

template<class T>
typename veqtor<T>::iterator veqtor<T>::erase(veqtor<T>::iterator it) {
    for(veqtor<T>::iterator i = it; i != end(); ++i)  *i = *(i + 1);
    _size -= 1;
    return it;
}

template<class T>
typename veqtor<T>::iterator veqtor<T>::erase(veqtor<T>::iterator it1, veqtor<T>::iterator it2) {
    int diff = it2 - it1;
    for(veqtor<T>::iterator i = it1; i != end() - diff; i++)  *i = *(i + diff);
    _size = _size - diff;
    return it1;
}

template<class T>
void veqtor<T>::clear() { erase(begin(),end()); }
