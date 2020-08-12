#ifndef TASKPRIORITYCONTAINER_H
#define TASKPRIORITYCONTAINER_H

#include "taskcontainer.h"
#include "taskpriority.h"

template <class T>
class TaskPriorityContainer : public TaskContainer, public TaskPriority<T> {
private:

public:
    TaskPriorityContainer(T p_priority, const std::string p_label =std::string(), const std::string p_desc =std::string(), std::string* p_list =nullptr, AbsTask* p_parent =nullptr);

    //AbsTask* getMaxPriorityChild();
};

template<class T>
TaskPriorityContainer<T>::TaskPriorityContainer(T p_priority, const std::string p_label, const std::string p_desc, std::string *p_list, AbsTask *p_parent)
    : AbsTask(p_label,p_desc,p_list,p_parent), TaskContainer(p_label,p_desc,p_list,p_parent), TaskPriority<T>(p_priority,p_label,p_desc,p_list,p_parent) {}


#endif // TASKPRIORITYCONTAINER_H
