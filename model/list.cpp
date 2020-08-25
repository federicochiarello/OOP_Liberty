#include "list.h"

unsigned short int List::nextID = 0;

List::List(const std::string p_name) : m_name(p_name), id(++nextID) {}

List::List(const List &p_list) : m_name(p_list.m_name), m_tasks(p_list.m_tasks), m_tasksOrder(p_list.m_tasksOrder), id(++nextID) {}

List::~List() {
    if(! m_tasks.empty())
        for(std::map<unsigned short int,AbsTask*>::iterator i=m_tasks.begin(); i!=m_tasks.end(); i++)
            delete i->second;
}

std::string List::getName() const { return m_name; }

unsigned short List::getId() const { return id; }

void List::setName(const std::string & p_name) { m_name = p_name; }

void List::addTask(AbsTask * p_task) {
    p_task->setList(this);
    std::map<unsigned short int,AbsTask*>::value_type t(p_task->getId(),p_task);
    m_tasks.insert(t);
    m_tasksOrder.push_back(p_task->getId());
}

void List::removeTask(const unsigned short int idTask) {
    AbsTask* t = m_tasks.at(idTask);
    t->setList(nullptr);
    if(!t->getParent())
        for(std::vector<unsigned short int>::iterator i = m_tasksOrder.begin(); i != m_tasksOrder.end(); i++)
            if (*i == idTask) {
                m_tasksOrder.erase(i);
                i = m_tasksOrder.end();
            }
    m_tasks.erase(idTask);
}

void List::updateTask(const unsigned short int idTask, AbsTask *p_task) {
    if(!m_tasks.at(idTask)->getParent())
        for(std::vector<unsigned short int>::iterator i = m_tasksOrder.begin(); i != m_tasksOrder.end(); i++)
            if (*i == idTask) {
                *i = p_task->getId();
                i = m_tasksOrder.end();
            }

    m_tasks.erase(idTask);
    addTask(p_task);
}

void List::setAsDirectTask(const unsigned short idTask) {
    m_tasksOrder.push_back(idTask);
}

AbsTask *List::getTask(const unsigned short idTask) {
    return m_tasks.at(idTask);
}

