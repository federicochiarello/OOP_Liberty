#include "project.h"
#include<iostream>

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

QStringList Project::getTaskInfo(const unsigned short idList, const unsigned short idTask) const {
    AbsTask* t = m_lists.at(idList)->getTask(idTask);
    QStringList tmp;

    TaskPriority* tPrio = dynamic_cast<TaskPriority*>(t);
    TaskContainer* tCont = dynamic_cast<TaskContainer*>(t);
    if(!tPrio && !tCont)  tmp.push_back("Task");
    else
        if(tPrio)
            if(tCont)   tmp.push_back("PriorityContainer");
            else        tmp.push_back("Priority");
        else            tmp.push_back("Container");

    tmp.push_back(QString::fromStdString(t->getLabel()));
    tmp.push_back(QString::fromStdString(t->getDesc()));
    tmp.push_back(t->getEta().toString("dd.MM.yyyy hh:mm:ss"));

    if(tPrio)
        tmp.push_back(tPrio->getPriority().toString("dd.MM.yyyy hh:mm:ss"));
    if(tCont) {
        std::vector<AbsTask*> v = tCont->getChilds();
        for(std::vector<AbsTask*>::iterator i = v.begin(); i != v.end(); i++)
            tmp.push_back(QVariant((*i)->getId()).toString());
    }

    return tmp;
}

void Project::aggiornaTask(const unsigned short int idList, const unsigned short int idTask, const QStringList info) {
    m_lists.at(idList)->getTask(idTask)->aggiornaTask(info);
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

unsigned short Project::addNewTask(const unsigned short idList) {
    // aggiunto un nuovo task alla lista (figlio diretto)
    AbsTask* t = new Task;
    List* l = m_lists.at(idList);

    l->addTask(t);
    l->setAsDirectTask(t->getId());
    return t->getId();
}

unsigned short Project::addNewTask(const unsigned short idList, const unsigned short idTask) {
    // aggiunto un nuovo task alla lista (figlio di task(idTask))
    List* l = m_lists.at(idList);
    AbsTask* tParent = l->getTask(idTask);

    AbsTask* t = new Task;
    l->addTask(t);
    dynamic_cast<TaskContainer*>(tParent)->addChild(t);
    return t->getId();
}

/*
void Project::addNewTask(const unsigned short int idList, AbsTask* p_task) {
    m_lists.at(idList)->addTask(p_task);
}
void Project::addNewList() {
    List* newList = new List();
    std::map<unsigned short int,List*>::value_type l(newList->getId(),newList);
    m_lists.insert(l);
    m_listsOrder.push_back(newList->getId());
}
*/
unsigned short Project::addNewList() {
    List* newList = new List();
    unsigned short int id = newList->getId();
    std::map<unsigned short int,List*>::value_type l(id,newList);
    m_lists.insert(l);
    m_listsOrder.push_back(id);
    return id;
}

unsigned short int Project::convertToPriority(const unsigned short int idList, const unsigned short int idTask) {
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
    return tNew->getId();
}

unsigned short int Project::convertToContainer(const unsigned short int idList, const unsigned short int idTask) {
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
    return tNew->getId();
}

void Project::dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione) {
    List* lp = m_lists.at(LPartenza);
    List* la = m_lists.at(LArrivo);
    AbsTask* t = lp->getTask(idTask);

    lp->removeTask(idTask);
    la->addTask(t);
    la->insertTask(Posizione,idTask);
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
