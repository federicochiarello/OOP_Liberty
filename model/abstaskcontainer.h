#ifndef ABSTASKCONTAINER_H
#define ABSTASKCONTAINER_H

#include "abstask.h"

class AbsTaskContainer : virtual public AbsTask {
private:
public:
	AbsTaskContainer();
	virtual ~AbsTaskContainer();
};

#endif // ABSTASKCONTAINER_H
