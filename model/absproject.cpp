#include "absproject.h"

AbsProject::AbsProject(std::string p_name) : m_name(p_name) {}

AbsProject::~AbsProject() {}

void AbsProject::addList(List *p_list) { m_lists.push_back(p_list); }

void AbsProject::removeList(List *p_list) {
    // Se p_list ha figli -> eliminali
    std::vector<AbsTask*> children = p_list->getListChildren();
    if(! children.empty())
        for(std::vector<AbsTask*>::iterator i = children.begin(); i != children.end(); i++)
            delete *i;

    // Elimina p_list
    std::vector<List*>::iterator i = m_lists.begin();
    bool trovato = false;
    while( !trovato && i != m_lists.end()){
        if (*i == p_list) {
            m_lists.erase(i);
            trovato = true;
        }
        i++;
    }
}

void AbsProject::setName(const std::string& p_name) { m_name = p_name; }

void AbsProject::setListName(const unsigned int indL, const std::string& p_name) {
    getList(indL)->setName(p_name);
}

std::string AbsProject::getName() const { return m_name; }

std::vector<List *> AbsProject::getLists() const { return m_lists; }

List *AbsProject::getList(const unsigned int indL) const {
    return m_lists[indL];
}

void AbsProject::addNewTask(const unsigned int indL, AbsTask* p_task) {
    getList(indL)->addNewTask(p_task);
}

void AbsProject::addNewList() {
    m_lists.push_back(new List());
}
