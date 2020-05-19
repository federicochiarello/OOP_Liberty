#ifndef ABSTASKPRIO_H
#define ABSTASKPRIO_H

#include "abstask.h"

template <class T>
class AbsTaskPrio : virtual public AbsTask {
	T m_priority;
public:
	AbsTaskPrio();
};

#endif // ABSTASKPRIO_H
