#include "project.h"

Project::Project(std::string p_name) : m_name(p_name) {}

Project::~Project() {}

void Project::addList(List *p_list) { m_lists.push_back(p_list); }

void Project::removeList(List *p_list) {
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

void Project::setName(const std::string& p_name) { m_name = p_name; }

void Project::setListName(const unsigned short int idList, const std::string& p_name) {
    getList(idList)->setName(p_name);
}

std::string Project::getName() const { return m_name; }

std::vector<List *> Project::getLists() const { return m_lists; }

List *Project::getList(const unsigned int indL) const {
    return m_lists[indL];
}

void Project::addNewTask(const unsigned int indL, AbsTask* p_task) {
    getList(indL)->addNewTask(p_task);
}

void Project::addNewList() {
    m_lists.push_back(new List());
}
/*
void Project::ConvertToPriority(const unsigned int indL, const unsigned int indT) {
    List* l = getList(indL);
    AbsTask* tmp = l->getTask(indT);
    if(dynamic_cast<TaskContainer*>(tmp))
        tmp = new TaskPriorityContainer(tmp->getLabel(),tmp->getDesc(),tmp->getList(),tmp->getParent());
    else
        tmp = new TaskPriority(tmp->getLabel(),tmp->getDesc(),tmp->getList(),tmp->getParent());
    l->updateTask(indT,tmp);
}
*/

/*
template <class T>
QJsonDocument Project<T>::toJson() const {
	QJsonDocument doc;
	QJsonObject obj;
	obj.insert("name", m_name);
	QJsonArray tasks;
	for (auto it = m_tasks.begin(); it != m_tasks.end(); it++) {
		tasks.append(it->toJson());
	}
	obj.insert("tasks", tasks);
	doc.setArray(tasks);
}
*/
