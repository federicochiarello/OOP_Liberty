#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

template <class T>
class container {
private:
	unsigned int						m_size;
	unsigned int						m_capacity;
	T*									m_vector;



public:
										container();
										container(const container&);
										~container();

	void								pushFront(const T&);
	void								pushBack(const T&);
	void								popFront();
	void								popBack();

	class iterator {
	private:
		T**								m_pointer;
	public:
										iterator();
	};

};

#endif // CONTAINER_H
