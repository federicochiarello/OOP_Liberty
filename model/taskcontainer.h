#ifndef TASKCONTAINER_H
#define TASKCONTAINER_H

#include "abstask.h"
#include <vector>

class TaskContainer : virtual public AbsTask {
private:
    std::vector<AbsTask*>				m_child;

public:
                                        TaskContainer(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr);
                                        TaskContainer(const TaskContainer& p_task);

    TaskContainer*                      clone() const override;
    void                                setList(List* p_list) override;

    std::vector<AbsTask*>				getChilds() const;
    void								addChild(AbsTask*);
    void                                removeChild(AbsTask*);
    void                                addChildList(std::vector<AbsTask*> p_child);
    void                                updateChild(AbsTask* tOld, AbsTask* tNew);
};

#endif // TASKCONTAINER_H
