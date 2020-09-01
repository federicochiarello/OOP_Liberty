#include "project.h"

unsigned short Project::nextID = 0;

Project::Project(std::string p_name) :
	_id(++nextID),
	m_name(p_name),
    m_lists(std::map<unsigned short, List*>()),
    m_listsOrder(std::vector<unsigned short>()),
	_modified(true) {}

Project::Project(const QJsonObject& object) :
	_id(++nextID),
	m_name(object.value("projectName").toString().toStdString()),
    m_lists(std::map<unsigned short, List*>()),
    m_listsOrder(std::vector<unsigned short>()),
	_modified(false) {

	qDebug() << "Progetto creato";

	std::vector<AbsTask*> tasks;
    std::map<unsigned short,unsigned short> idsMap;
    std::map<unsigned short, std::vector<unsigned short>> childsMap;

	const QJsonArray listsArray = object.value("lists").toArray();
	for (const QJsonValue list : listsArray) {
		List* tmp = new List(list.toObject(), tasks, idsMap);
        m_lists.insert(std::pair<unsigned short, List*>(tmp->getId(), tmp));
		m_listsOrder.push_back(tmp->getId());
	}
//	Le liste sono state create e ogni task ha puntatore alla lista, però mancano da inizializzare i vector childs nei TaskContainer e i puntatori a parent dei task figli

//	Itero il vector contenente tutti i task per individuare i TaskContainer, dei quali bisogna aggiungere i Task figli
	for (auto task : tasks) {
		TaskContainer* taskContainer = dynamic_cast<TaskContainer*>(task);
//		Verifico che il task considerato nell'i-esima iterazione sia un TaskContainer o una sua sottoclasse
		if (taskContainer) {
//			Ricavo il vector contenente gli Id dei Task figli
            std::vector<unsigned short> taskContainerChildsId = childsMap.find(taskContainer->getId())->second;
//			Itero nuovamente il vector contenente tutti i task per individuare i Task figli di taskContainer
			for (auto childTask : tasks) {
                const unsigned short childTaskId = childTask->getId();
//				Itero il vector contenente gli Id dei task figli di taskContainer per verificare se il childTask considerato nella i,j-esima iterazione abbia Id uguale ad uno dei figli
				for (auto id : taskContainerChildsId) {
					if (childTaskId == id) {
//						In caso positivo significa che esso é un figlio di taskContainer e quindi lo aggiungo come figlio
						taskContainer->addChild(childTask);
					}
//					childTask non é figlio di task, proseguo ad iterare tasks alla ricerca di figli
				}
//				Terminato di inserire i figli in task
			}
		}
//		Il task considerato non é un TaskContainer, quindi continuo ad iterare
	}
}

Project::~Project() {
    if(! m_lists.empty())
        for(auto i=m_lists.begin(); i!=m_lists.end(); i++)
            delete i->second;
}

void Project::addList(List *p_list) {
//	std::map<unsigned short,List*>::value_type l(p_list->getId(),p_list);
	m_lists.insert(std::pair<unsigned short, List*>(p_list->getId(), p_list));
	m_listsOrder.push_back(p_list->getId());
}

void Project::removeList(unsigned short idList) {

    // Se p_list ha figli -> eliminali
    delete m_lists.at(idList);

    // Elimina da m_listOrder
    for(auto i = m_listsOrder.begin(); i != m_listsOrder.end(); i++)
        if (*i == idList) {
            m_listsOrder.erase(i);
            i = m_listsOrder.end();
        }
}

unsigned short Project::getId() const {
	return _id;
}

void Project::setName(const std::string& p_name) { m_name = p_name; }

QString Project::getListName(const unsigned short listId) const {
	return QString::fromStdString(m_lists.at(listId)->getName());
}

void Project::setListName(const unsigned short idList, const std::string& p_name) {
    m_lists.at(idList)->setName(p_name);
}

void Project::changeListOrder(const unsigned short listToMove, const unsigned short Posizione) {
	if(!Posizione) {
        m_listsOrder.insert(m_listsOrder.begin(),listToMove);
	} else {
		for(auto i = m_listsOrder.begin(); i < m_listsOrder.end(); i++) {
            if (*i == Posizione) {
                m_listsOrder.insert(i,listToMove);
                i = m_listsOrder.end();
            }
		}
	}
}

std::vector<std::pair<unsigned short, TaskType> > Project::getTasksIds(const unsigned short listId) const {
	return m_lists.at(listId)->getTasksIds();
}

QStringList Project::getTaskInfo(const unsigned short idList, const unsigned short idTask) const {
    return m_lists.at(idList)->getTask(idTask)->getTaskInfo();
}

std::string Project::getTaskName(const unsigned short idList, const unsigned short idTask) const {
    return m_lists.at(idList)->getTask(idTask)->getLabel();
}

QDateTime Project::getTaskPriority(const unsigned short idList, const unsigned short idTask) const {
    return dynamic_cast<TaskPriority*>(m_lists.at(idList)->getTask(idTask))->getPriority();
    /*
    TIPO DI RITORNO std::string

    TaskPriority* t = dynamic_cast<TaskPriority*>(m_lists.at(idList)->getTask(idTask));
    if(t)
        return t->getPriority().toString("dd/MM/yyyy hh:mm:ss").toStdString();
    else
        return "ERROR";
    */
}

void Project::aggiornaTask(const unsigned short idList, const unsigned short idTask, const QStringList info) {
    m_lists.at(idList)->getTask(idTask)->aggiornaTask(info);
}

unsigned short Project::verifyContainer(const unsigned short idList, const unsigned short idTask) {
    // se idTask è un TaskContainer -> ritorna il il suo id
    //                   altrimenti -> lo converte a TaskContainer e ritorna il nuovo id
    return (dynamic_cast<TaskContainer*>(m_lists.at(idList)->getTask(idTask)) == nullptr ? convertToPriority(idList,idTask) : idTask );
}

std::string Project::getName() const { return m_name; }

std::vector<unsigned short> Project::getLists() const {
	return m_listsOrder;
}

Project* Project::fromJson(const QJsonObject& object) {
	std::vector<AbsTask*> tasks;
    std::map<unsigned short,unsigned short> idsMap;
    std::map<unsigned short, std::vector<unsigned short>> childsMap;
	m_name = object.value("projectName").toString().toStdString();
	const QJsonArray listsArray = object.value("lists").toArray();

	for (const QJsonValue list : listsArray) {
		List* tmp = new List(list.toObject(), tasks, idsMap);
		m_lists.insert(std::pair<unsigned short, List*>(tmp->getId(), tmp));
		m_listsOrder.push_back(tmp->getId());
	}
//	Le liste sono state create e ogni task ha puntatore alla lista, però mancano da inizializzare i vector childs nei TaskContainer e i puntatori a parent dei task figli

//	Itero il vector contenente tutti i task per individuare i TaskContainer, dei quali bisogna aggiungere i Task figli
	for (auto task : tasks) {
		TaskContainer* taskContainer = dynamic_cast<TaskContainer*>(task);
//		Verifico che il task considerato nell'i-esima iterazione sia un TaskContainer o una sua sottoclasse
		if (taskContainer) {
//			Ricavo il vector contenente gli Id dei Task figli
            std::vector<unsigned short> taskContainerChildsId = childsMap.find(taskContainer->getId())->second;
//			Itero nuovamente il vector contenente tutti i task per individuare i Task figli di taskContainer
			for (auto childTask : tasks) {
				const unsigned short childTaskId = childTask->getId();
//				Itero il vector contenente gli Id dei task figli di taskContainer per verificare se il childTask considerato nella i,j-esima iterazione abbia Id uguale ad uno dei figli
				for (auto id : taskContainerChildsId) {
					if (childTaskId == id) {
//						In caso positivo significa che esso é un figlio di taskContainer e quindi lo aggiungo come figlio
						taskContainer->addChild(childTask);
					}
//					childTask non é figlio di task, proseguo ad iterare tasks alla ricerca di figli
				}
//				Terminato di inserire i figli in task
			}
		}
//		Il task considerato non é un TaskContainer, quindi continuo ad iterare
	}
    return this;
}

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

AbsTask *Project::getPointer(const unsigned short idList, const unsigned short idTask) {
    return m_lists.at(idList)->getTask(idTask);
}

unsigned short Project::addNewList() {
    List* newList = new List();
    unsigned short id = newList->getId();
    m_lists.insert(std::pair<unsigned short, List*>(id,newList));
    m_listsOrder.push_back(id);
    return id;
}

unsigned short Project::convertToPriority(const unsigned short idList, const unsigned short idTask) {
    List* l = m_lists.at(idList);
    AbsTask* t = l->getTask(idTask);
    AbsTask* tNew = t->convertToPriority();

    if(!tNew) return 0;
    else {
        //  Sostituito t (non Priority) con tNew (Priority)
        l->updateTask(idTask,tNew);
        //  Se t ha (parent != nullptr) va aggiornato il padre
        if(t->getParent())
            dynamic_cast<TaskContainer*>(t->getParent())->updateChild(t,tNew);
        delete t;
        return tNew->getId();
    }
}

unsigned short Project::convertToContainer(const unsigned short idList, const unsigned short idTask) {
    List* l = m_lists.at(idList);
    AbsTask* t = l->getTask(idTask);
    AbsTask* tNew = t->convertToContainer();

    if(!tNew) return 0;
    else {
        l->updateTask(idTask,tNew);
        if(t->getParent())
            dynamic_cast<TaskContainer*>(t->getParent())->updateChild(t,tNew);
        delete t;
        return tNew->getId();
    }
}

void Project::dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione) {
    // Versione funzionante in cui un task (idTask) viene spostato dalla lista LPartenza alla lista
    // LArrivo sotto al task con id Posizione, se Posizione == 0 viene messo in testa alla lista.

    List* lp = m_lists.at(LPartenza);
    List* la = m_lists.at(LArrivo);
    AbsTask* t = lp->getTask(idTask);

    if(t->getParent())
        dynamic_cast<TaskContainer*>(t->getParent())->removeChild(t);
    lp->removeTask(idTask);
    la->addTask(t);
    la->insertTask(idTask,Posizione);
}

QJsonObject Project::object() {

	QJsonObject projectObject;

	projectObject.insert("projectId", QJsonValue(_id));
	projectObject.insert("projectName", QJsonValue(QString::fromStdString(m_name)));
	QJsonArray lists;
	for (auto it = m_lists.begin(); it != m_lists.end(); it++) {
		lists.append(it->second->toJson());
	}
	projectObject.insert("lists", lists);
	_modified = false;

	return projectObject;
}
