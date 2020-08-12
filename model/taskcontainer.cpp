#include "taskcontainer.h"

TaskContainer::TaskContainer(const std::string p_label, const std::string p_desc, std::string* p_list, AbsTask* p_parent) :
    AbsTask(p_label,p_desc,p_list,p_parent) {}

void TaskContainer::setList(std::string *p_list) {
    this->AbsTask::setList(p_list);
    for(std::vector<AbsTask*>::iterator i = m_child.begin(); i != m_child.end(); i++) {
        (*i)->setList(p_list);
    }
}

std::vector<AbsTask *> TaskContainer::getChilds() const {
    return m_child;
}

void TaskContainer::addChild(AbsTask * p_child) {
    m_child.push_back(p_child);
}

void TaskContainer::removeChild(const AbsTask * p_child) {
    std::vector<AbsTask*>::iterator i = m_child.begin();
    bool trovato = false;
    while(trovato == false && i != m_child.end()){
        if (*i == p_child) {
            m_child.erase(i);
            trovato = true;
        }
        i++;
    }
}
