#ifndef TASKPRIORITYCONTAINER_H
#define TASKPRIORITYCONTAINER_H

#include "taskcontainer.h"
#include "taskpriority.h"

template <class T>
class TaskPriorityContainer : public TaskContainer, public TaskPriority<T> {
private:

public:
    TaskPriorityContainer(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr, T p_priority =T());

    TaskPriorityContainer<T>*               clone() const override;

    void                                    setPriority(T p_priority) override;

    //AbsTask* getMaxPriorityChild();
};

template<class T>
TaskPriorityContainer<T>::TaskPriorityContainer(const std::string p_label, const std::string p_desc, List *p_list, AbsTask *p_parent, T p_priority)
    : AbsTask(p_label,p_desc,p_list,p_parent), TaskContainer(p_label,p_desc,p_list,p_parent), TaskPriority<T>(p_label,p_desc,p_list,p_parent,p_priority) {}

template<class T>
TaskPriorityContainer<T> *TaskPriorityContainer<T>::clone() const { return new TaskPriorityContainer<T>(*this); }

template<class T>
void TaskPriorityContainer<T>::setPriority(T p_priority) {
    this->TaskPriority<T>::setPriority(p_priority);
    std::vector<AbsTask*> tmp = this->getChilds();
    for(std::vector<AbsTask*>::iterator i = tmp.begin(); i != tmp.end(); i++) {
        TaskPriority<T>* p = dynamic_cast<TaskPriority<T>*>(*i);
        if( p && p->getPriority() >= p_priority )
            p->setPriority(p_priority);
    }
}

#endif // TASKPRIORITYCONTAINER_H
