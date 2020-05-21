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

    class iterator{
    public:

        iterator(): v(nullptr), i(0) {}
        iterator(veqtor<T>* vet, int n): v(vet),       i(n) {}

        T&                  operator*()             { return (*v)[i]; }
        const T&            operator*()       const { return (*v)[i]; }
        T*                  operator->()            { return &((*v)[i]); }
        const T*            operator->()      const { return &((*v)[i]); }
        T&                  operator[](int n)       { return (*v)[i + n]; }
        const T&            operator[](int n) const { return (*v)[i + n]; }

        iterator&           operator++()       { ++i; return *this; }
        iterator&           operator--()       { --i; return *this; }
        iterator            operator++(int)    { iterator aux(*this); ++i; return aux; }
        iterator            operator--(int)    { iterator aux(*this); --i; return aux; }

        iterator&           operator+=(int n)  { i += n; return *this; }
        iterator&           operator-=(int n)  { i -= n; return *this; }

        iterator            operator+(int n)   const { iterator r(*this); return r += n; }
        iterator            operator-(int n)   const { iterator r(*this); return r -= n; }

        bool                operator<(iterator const& r)  const { return i <  r.i; }
        bool                operator<=(iterator const& r) const { return i <= r.i; }
        bool                operator>(iterator const& r)  const { return i >  r.i; }
        bool                operator>=(iterator const& r) const { return i >= r.i; }
        bool                operator!=(const iterator &r) const { return i != r.i; }
        bool                operator==(const iterator &r) const { return i == r.i; }

        int                 operator-(iterator it) const { return i - it.i; }

        operator int() { return i; }

    //private:
        const               veqtor<T>* v;
        int                 i;
    };

    veqtor();
    veqtor(unsigned short);
    veqtor(unsigned short, const T&);
    veqtor(const iterator&,const iterator&);
    veqtor(const veqtor&);
    ~veqtor();

    veqtor<T>&              operator=(const veqtor<T>&);
    unsigned short          capacity() const;
    unsigned short          size() const;
    bool                    empty() const;
    void                    push_back(const T&);
    void                    pop_back();
    T&                      operator[](unsigned int) const;
    iterator                begin() const;
    iterator                end() const;
    void                    insert(veqtor<T>::iterator, const int&, const T&);
    veqtor<T>::iterator     insert(veqtor<T>::iterator, const T&);
    template<class inputIt>
    void                    insert(veqtor<T>::iterator,inputIt,inputIt);
    //***************************************************************************************************************************
    // comportamento un po diverso da standard
    veqtor<T>::iterator     erase(veqtor<T>::iterator);
    veqtor<T>::iterator     erase(veqtor<T>::iterator, veqtor<T>::iterator);
    void                    clear();

};
#endif
