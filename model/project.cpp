#include "project.h"

Project::Project(std::string p_name) : m_name(p_name) {}

//Project::Project(QJsonObject& object) {}

Project::~Project() {
    if(! m_lists.empty())
        for(std::map<unsigned short int,List*>::iterator i=m_lists.begin(); i!=m_lists.end(); i++)
            delete i->second;
}

void Project::addList(List *p_list) {
    std::map<unsigned short int,List*>::value_type l(p_list->getId(),p_list);
    m_lists.insert(l);
}

void Project::removeList(unsigned short int idList) {

    // Se p_list ha figli -> eliminali
    delete m_lists.at(idList);

    // Elimina da m_listOrder
    for(std::vector<unsigned short int>::iterator i = m_listsOrder.begin(); i != m_listsOrder.end(); i++)
        if (*i == idList) {
            m_listsOrder.erase(i);
            i = m_listsOrder.end();
        }
}

void Project::setName(const std::string& p_name) { m_name = p_name; }

void Project::setListName(const unsigned short int idList, const std::string& p_name) {
    m_lists.at(idList)->setName(p_name);
}

std::string Project::getName() const { return m_name; }

Project* Project::fromJson(const QJsonObject& object) {
	m_name = object.value("projectName").toString().toStdString();
	const QJsonArray listsArray = object.value("lists").toArray();
	for (const QJsonValue list : listsArray) {
		List* tmp = new List(list.toObject());
		m_lists.insert(std::pair<unsigned short, List*>(tmp->getId(), tmp));
		m_listsOrder.push_back(tmp->getId());
	}
	return this;
}

//std::vector<List *> Project::getLists() const { return m_lists; }

void Project::addNewTask(const unsigned short int idList, AbsTask* p_task) {
    m_lists.at(idList)->addTask(p_task);
}

void Project::addNewList() {
    List* newList = new List();
    std::map<unsigned short int,List*>::value_type l(newList->getId(),newList);
    m_lists.insert(l);
    m_listsOrder.push_back(newList->getId());
}

void Project::convertToPriority(const unsigned short int idList, const unsigned short int idTask) {
    //  l lista da cui prendere task t da trasformare in priority
    List* l = m_lists.at(idList);
    AbsTask* t = l->getTask(idTask), * tNew;

    //  2 casi: t è TaskContainer / no
    TaskContainer* tCont = dynamic_cast<TaskContainer*>(t);
    if(tCont) {
        tNew = new TaskPriorityContainer(t->getLabel(),t->getDesc());
        dynamic_cast<TaskContainer*>(tNew)->addChildList(tCont->getChilds());
    } else
        tNew = new TaskPriority(t->getLabel(),t->getDesc());

    //  Sostituito t (non Priority) con tNew (Priority)
    l->updateTask(idTask,tNew);

    //  Se t ha (parent != nullptr) va aggiornato il padre
    if(t->getParent())
        dynamic_cast<TaskContainer*>(t->getParent())->updateChild(t,tNew);

    delete t;
}

void Project::convertToContainer(const unsigned short int idList, const unsigned short int idTask) {
    List* l = m_lists.at(idList);
    AbsTask* t = l->getTask(idTask), * tNew;

    TaskPriority* tPrio = dynamic_cast<TaskPriority*>(t);
    if(tPrio)
        tNew = new TaskPriorityContainer(t->getLabel(),t->getDesc(),nullptr,nullptr,tPrio->getPriority());
    else
        tNew = new TaskContainer(t->getLabel(),t->getDesc());

    l->updateTask(idTask,tNew);

    if(t->getParent())
        dynamic_cast<TaskContainer*>(t->getParent())->updateChild(t,tNew);

    delete t;
}


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
