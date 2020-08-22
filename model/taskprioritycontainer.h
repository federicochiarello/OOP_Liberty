#ifndef TASKPRIORITYCONTAINER_H
#define TASKPRIORITYCONTAINER_H

#include "taskcontainer.h"
#include "taskpriority.h"

class TaskPriorityContainer : public TaskContainer, public TaskPriority {
public:
    TaskPriorityContainer(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr, QDateTime p_priority =QDateTime());

    TaskPriorityContainer*                  clone() const override;

    void                                    setPriority(QDateTime p_priority) override;

};

#endif // TASKPRIORITYCONTAINER_H
