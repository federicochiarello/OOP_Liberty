#ifndef VEQTOR_H
#define VEQTOR_H

template<class T>
class veqtor {
private:
    T*                      _pointer;
    unsigned short          _size;
    unsigned short          _capacity;

    void                    expand();
public:
    veqtor();
    veqtor(unsigned short, const T&);
    //veqtor(iterator,iterator);
    veqtor(const veqtor&);
    ~veqtor();

    veqtor<T>&              operator=(const veqtor<T>&);
    unsigned short          capacity() const;
    unsigned short          size() const;
    bool                    empty() const;
    void                    pushFront(const T&);
    void                    pushBack(const T&);
    T                       popFront();
    T                       popBack();
    T&                      operator[](unsigned short) const;

};
#endif // VEQTOR_H
