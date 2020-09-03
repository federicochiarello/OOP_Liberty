#include "project.h"

unsigned short Project::nextID = 0;

Project::Project(std::string p_name) :
	_id(++nextID),
	m_name(p_name),
    m_lists(std::map<unsigned short, List*>()),
    m_listsOrder(veqtor<unsigned short>()),
	_modified(true) {}

Project::Project(const QJsonObject& object) :
	_id(++nextID),
	m_name(object.value("projectName").toString().toStdString()),
	m_lists(std::map<unsigned short, List*>()),
    m_listsOrder(veqtor<unsigned short>()),
	_modified(false) {

    veqtor<AbsTask*> tasks;
    std::map<unsigned short,unsigned short> idsMap;
    std::map<unsigned short, veqtor<unsigned short>> childsMap;

	const QJsonArray listsArray = object.value("lists").toArray();
	for (const QJsonValue list : listsArray) {
		List* tmp = new List(list.toObject(), tasks, idsMap, childsMap);
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
            veqtor<unsigned short> taskContainerChildsId = childsMap.find(taskContainer->getId())->second;
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
	_modified = true;
	m_lists.insert(std::pair<unsigned short, List*>(p_list->getId(), p_list));
	m_listsOrder.push_back(p_list->getId());
}

void Project::removeList(unsigned short listId) {
	_modified = true;

	// Se p_list ha figli -> eliminali
    delete m_lists.at(listId);

    // Elimina da m_listOrder
    for(auto i = m_listsOrder.begin(); i != m_listsOrder.end(); i++)
        if (*i == listId) {
            m_listsOrder.erase(i);
            i = m_listsOrder.end();
        }
}

unsigned short Project::getId() const {
	return _id;
}

void Project::setName(const std::string& p_name) {
	_modified = true;
	m_name = p_name;
}

QString Project::getListName(const unsigned short listId) const {
	return QString::fromStdString(m_lists.at(listId)->getName());
}

void Project::setListName(const unsigned short listId, const std::string& p_name) {
	_modified = true;
    m_lists.at(listId)->setName(p_name);
}

void Project::setTaskName(const unsigned short listId, const unsigned short taskId, const std::string &newTaskName) {
    m_lists.at(listId)->setTaskName(taskId, newTaskName);
}

bool Project::changeListOrder(const unsigned short listToMove, const Direction& moveDirection) {
     for (auto i = m_listsOrder.begin(); i < m_listsOrder.end(); ++i)
		 if(*i == listToMove) {
			 if(moveDirection == LEFT  && (i-1) >= m_listsOrder.begin()) {
				 _modified = true;

				 unsigned short tmp = *i;
				 *i = *(i-1);
				 *(i-1) = tmp;

				 return true;
			 } else if(moveDirection == RIGHT  && (i+1) < m_listsOrder.end()) {
				 _modified = true;

				 unsigned short tmp = *i;
				 *i = *(i+1);
				 *(i+1) = tmp;

				 return true;
			 }
		 }
	 return false;
}

veqtor<std::pair<unsigned short, TaskType>> Project::getTasksIds(const unsigned short listId) const {
	return m_lists.at(listId)->getTasksIds();
}

QStringList Project::getTaskInfo(const unsigned short listId, const unsigned short taskId) const {
    return m_lists.at(listId)->getTask(taskId)->getTaskInfo();
}

std::string Project::getTaskName(const unsigned short listId, const unsigned short taskId) const {
    return m_lists.at(listId)->getTask(taskId)->getLabel();
}

QDateTime Project::getTaskPriority(const unsigned short listId, const unsigned short taskId) const {
    return dynamic_cast<TaskPriority*>(m_lists.at(listId)->getTask(taskId))->getPriority();
}

void Project::aggiornaTask(const unsigned short listId, const unsigned short taskId, const QStringList info) {
	_modified = true;
    m_lists.at(listId)->getTask(taskId)->aggiornaTask(info);
}

void Project::deleteTask(const unsigned short listId, const unsigned short taskId) {
    _modified = true;
    m_lists.at(listId)->deleteTask(taskId);
}

unsigned short Project::cloneTask(const unsigned short listId, const unsigned short taskId) {
    // crea una copia (con id differente) del task contraddistinto da taskId
    List* l = m_lists.at(listId);
    AbsTask* t = l->getTask(taskId)->clone();
    l->addTask(t);
    l->setAsDirectTask(t->getId());
    return t->getId();
}

std::string Project::getName() const { return m_name; }

veqtor<unsigned short> Project::getLists() const {
	return m_listsOrder;
}

Project* Project::fromJson(const QJsonObject& object) {
	_modified = true;
    veqtor<AbsTask*> tasks;
    std::map<unsigned short,unsigned short> idsMap;
    std::map<unsigned short, veqtor<unsigned short>> childsMap;
	m_name = object.value("projectName").toString().toStdString();
	const QJsonArray listsArray = object.value("lists").toArray();

	for (const QJsonValue list : listsArray) {
		List* tmp = new List(list.toObject(), tasks, idsMap, childsMap);
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
            veqtor<unsigned short> taskContainerChildsId = childsMap.find(taskContainer->getId())->second;
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

unsigned short Project::addNewTask(const unsigned short listId) {
	_modified = true;
    // aggiunto un nuovo task alla lista (figlio diretto)
    List* list = m_lists.at(listId);
	AbsTask* task = new Task(list);

	list->addTask(task);
	list->setAsDirectTask(task->getId());
	return task->getId();
}

unsigned short Project::addNewTask(const unsigned short listId, const unsigned short taskId) {
	_modified = true;
	// aggiunto un nuovo task alla lista (figlio di task(idTask))
    List* l = m_lists.at(listId);
    AbsTask* tParent = l->getTask(taskId);
    AbsTask* t = new Task;
    l->addTask(t);
    dynamic_cast<TaskContainer*>(tParent)->addChild(t);
    return t->getId();
}

AbsTask *Project::getPointer(const unsigned short listId, const unsigned short taskId) const {
    return m_lists.at(listId)->getTask(taskId);
}

unsigned short Project::addNewList() {
	_modified = true;
    List* newList = new List();
    unsigned short id = newList->getId();
    m_lists.insert(std::pair<unsigned short, List*>(id,newList));
    m_listsOrder.push_back(id);
    return id;
}

void Project::convertToPriority(const unsigned short listId, const unsigned short taskId) {
    List* l = m_lists.at(listId);
    AbsTask* t = l->getTask(taskId);
    AbsTask* tNew = t->convertToPriority();

    if(tNew) {
        _modified = true;
        //  Aggiornata la lista (con il puntatore al task "convertito" inserito nella map
        l->aggiornaMap(tNew);
        //  Se t ha (parent != nullptr) va aggiornato il padre
        if(t->getParent())
            dynamic_cast<TaskContainer*>(t->getParent())->updateChild(t,tNew);
        delete t;
    }
}

void Project::convertToContainer(const unsigned short listId, const unsigned short taskId) {
    List* l = m_lists.at(listId);
    AbsTask* t = l->getTask(taskId);
    AbsTask* tNew = t->convertToContainer();

    if(tNew) {
        _modified = true;
        l->aggiornaMap(tNew);
        if(t->getParent())
            dynamic_cast<TaskContainer*>(t->getParent())->updateChild(t,tNew);
        delete t;
    }
}

void Project::dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short taskId, const unsigned short Posizione) {
	_modified = true;
	// Versione funzionante in cui un task (idTask) viene spostato dalla lista LPartenza alla lista
    // LArrivo sotto al task con id Posizione, se Posizione == 0 viene messo in testa alla lista.

    List* lp = m_lists.at(LPartenza);
    List* la = m_lists.at(LArrivo);
    AbsTask* t = lp->getTask(taskId);

    if(t->getParent())
        dynamic_cast<TaskContainer*>(t->getParent())->removeChild(t);
    lp->removeTask(taskId);
    la->addTask(t);
    la->insertTask(taskId,Posizione);
}


unsigned short Project::moveTask(const unsigned short listId, const unsigned short taskId, const Direction &moveDirection) {
	// trova posizione della lista target se esiste e la salva in it
	// se non esiste it = m_listOrder.end() che funge da sentinella
    veqtor<unsigned short>::iterator it = m_listsOrder.end();
	for (auto i = m_listsOrder.begin(); i < m_listsOrder.end(); ++i) {
        if(*i == listId) {
			if(moveDirection == LEFT  && (i-1) >= m_listsOrder.begin())
				it = i-1;
			else if(moveDirection == RIGHT  && (i+1) < m_listsOrder.end())
				it = i+1;
		 }
	}

	if(it == m_listsOrder.end()) {
		return 0;
	} else {
		_modified = true;

		unsigned short idTargetList = *it;
        List* l = m_lists.at(listId);
        AbsTask* t = l->getTask(taskId);
		List* targetList = m_lists.at(idTargetList);

        l->removeTask(taskId);
		targetList->addTask(t);
		targetList->setAsDirectTask(idTargetList);

		return idTargetList;
    }
}

bool Project::VmoveTask(const unsigned short listId, const unsigned short taskId, const VDirection &moveDirection) {
    _modified = m_lists.at(listId)->VmoveTask(taskId,moveDirection);
    return _modified;
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
