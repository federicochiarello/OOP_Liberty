#include "abstaskprio.h"

template <class T>
AbsTaskPrio<T>::AbsTaskPrio() : m_priority() {}

template<class T>
T AbsTaskPrio<T>::getPriority() const {
    return m_priority;
}

template<class T>
void AbsTaskPrio<T>::setPriority(T p_priority) {
    m_priority = p_priority;
}
