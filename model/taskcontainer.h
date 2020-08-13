#ifndef TASKCONTAINER_H
#define TASKCONTAINER_H

#include "abstask.h"
#include <vector>

class TaskContainer : virtual public AbsTask {
private:
    std::vector<AbsTask*>				m_child;

public:
                                        TaskContainer(const std::string p_label =std::string(), const std::string p_desc =std::string(), std::string* p_list =nullptr, AbsTask* p_parent =nullptr);
    virtual                             ~TaskContainer() override;

    /*  Override   */
    TaskContainer*                      clone() const override;
    void                                setList(std::string* p_list) override;

    /*  Get methods */
    std::vector<AbsTask*>				getChilds() const;

    /* Other methods */
    void								addChild(AbsTask*);
    void                                removeChild(const AbsTask*);
};

#endif // TASKCONTAINER_H
