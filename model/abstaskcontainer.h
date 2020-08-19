#ifndef ABSTASKCONTAINER_H
#define ABSTASKCONTAINER_H

#include <vector>

#include "abstask.h"

class AbsTaskContainer : virtual public AbsTask {
private:
	std::vector<AbsTask*>				m_child;

public:
    AbsTaskContainer(const std::string p_label =std::string(), const std::string p_desc =std::string(), AbsTask* p_parent =nullptr, std::string* p_list =nullptr);
    virtual ~AbsTaskContainer();

	/*  Get methods */
	std::vector<AbsTask*>				getChilds() const;

	/* Other methods */
    void								addChild(const AbsTask*);
    void                                removeChild(const AbsTask*);

};

#endif // ABSTASKCONTAINER_H
