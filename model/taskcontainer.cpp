#include "taskcontainer.h"

TaskContainer::TaskContainer(const std::string p_label, const std::string p_desc, List* p_list, AbsTask* p_parent) :
    AbsTask(p_label,p_desc,p_list,p_parent) {}

TaskContainer::TaskContainer(const TaskContainer & p_task) : AbsTask(p_task), m_child(p_task.m_child) {}

TaskContainer::~TaskContainer() {
    for(std::vector<AbsTask*>::iterator i=m_child.begin(); i!=m_child.end(); i++)
        delete *i;
}

TaskContainer *TaskContainer::clone() const { return new TaskContainer(*this); }

void TaskContainer::setList(List *p_list) {
    this->AbsTask::setList(p_list);
    for(std::vector<AbsTask*>::iterator i = m_child.begin(); i != m_child.end(); i++) {
        (*i)->setList(p_list);
    }
}

std::vector<AbsTask *> TaskContainer::getChilds() const {
    return m_child;
}

void TaskContainer::addChild(AbsTask * p_child) {
    p_child->setParent(this);
    m_child.push_back(p_child);
}

void TaskContainer::removeChild(AbsTask * p_child) {
    std::vector<AbsTask*>::iterator i = m_child.begin();
    bool trovato = false;
    while(!trovato && i != m_child.end()){
        if (*i == p_child) {
            p_child->setParent(nullptr);
            m_child.erase(i);
            trovato = true;
        }
        i++;
    }
}
