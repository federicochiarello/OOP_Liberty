#include "list.h"

unsigned short int List::nextID = 0;

List::List(const std::string p_name) : m_name(p_name), id(++nextID) {}

List::List(const List &p_list) : m_name(p_list.m_name), m_tasks(p_list.m_tasks), id(++nextID) {}

std::string List::getName() const { return m_name; }

std::vector<AbsTask *> List::getListChildren() const { return m_tasks; }

unsigned short List::getId() const { return id; }

void List::setName(const std::string & p_name) { m_name = p_name; }

void List::addTask(AbsTask * p_task) {
    p_task->setList(this);
    m_tasks.push_back(p_task);
}

void List::removeTask(AbsTask * p_task) {
    std::vector<AbsTask*>::iterator i = m_tasks.begin();
    bool trovato = false;
    while(trovato == false && i != m_tasks.end()){
        if (*i == p_task) {
            (*i)->setList(nullptr);
            m_tasks.erase(i);
            trovato = true;
        }
        i++;
    }
}

AbsTask *List::getTask(const unsigned int indT) const {
    return m_tasks[indT];
}

void List::updateTask(const unsigned int indT, AbsTask *p_task) {
    m_tasks.insert(m_tasks.erase(m_tasks.begin() + indT),p_task);
}

void List::addNewTask(AbsTask* p_task) {
    m_tasks.push_back(p_task);
}
