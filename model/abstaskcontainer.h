#ifndef ABSTASKCONTAINER_H
#define ABSTASKCONTAINER_H

#include <vector>

#include "abstask.h"

class AbsTaskContainer : virtual public AbsTask {
private:
	std::vector<AbsTask*>				m_child;
public:
    AbsTaskContainer();
	virtual ~AbsTaskContainer();

	/*  Get methods */
	std::vector<AbsTask*>				getChilds() const;

	/* Other methods */
    void								addChild(const AbsTask*);
    void                                removeChild(const AbsTask*);
};

#endif // ABSTASKCONTAINER_H
