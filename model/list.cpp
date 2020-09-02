#include "list.h"

unsigned short List::nextID = 0;

List::List(const unsigned short id, const std::string& name) :
	_id(id),
	m_name(name),
	m_tasks(std::map<unsigned short, AbsTask*>()),
	m_tasksOrder(std::vector<unsigned short>()) {}

List::List(const std::string& p_name) :
	_id(++nextID),
	m_name(p_name),
	m_tasks(std::map<unsigned short, AbsTask*>()),
	m_tasksOrder(std::vector<unsigned short>()) {}

List::List(const QJsonObject& object, std::vector<AbsTask*>& tasks, std::map<unsigned short,unsigned short>& idsMap, std::map<unsigned short, std::vector<unsigned short>>& childsMap) :
	_id(++nextID),
	m_name(object.value("listName").toString().toStdString()),
	m_tasks(std::map<unsigned short, AbsTask*>()),
	m_tasksOrder(std::vector<unsigned short>()) {

	qDebug() << "Lista creata";

	AbsTask* tmp = nullptr;
	for (const QJsonValue task : object.value("tasks").toArray()) {
		switch(task.toObject().value("taskType").toInt()) {
			case 1:
				tmp = new Task(task.toObject(), idsMap);
				break;
			case 2:
				tmp = new TaskContainer(task.toObject(), idsMap, childsMap);
				break;
			case 3:
				tmp = new TaskPriority(task.toObject(), idsMap);
				break;
			case 4:
				tmp = new TaskPriorityContainer(task.toObject(), idsMap, childsMap);
				break;
			default:
				tmp = nullptr;
		}
		if (tmp) {
            m_tasks.insert(std::pair<unsigned short, AbsTask*>(tmp->getId(), tmp));
			tasks.push_back(tmp);
			m_tasksOrder.push_back(tmp->getId());
		}
	}
}

List::List(const List &p_list) :
	_id(++nextID),
	m_name(p_list.m_name),
	m_tasks(p_list.m_tasks),
	m_tasksOrder(p_list.m_tasksOrder) {}

List::~List() {

	if(! m_tasks.empty()) {
		for(auto i=m_tasks.begin(); i!=m_tasks.end(); i++) {
            delete i->second;
			m_tasks.erase(i);
		}
	}
}

QJsonObject List::toJson() const {
	QJsonObject jsonObject;

	jsonObject.insert("listId", _id);
	jsonObject.insert("listName", QString::fromStdString(m_name));

	QJsonArray tasks;
	for (auto it = m_tasks.begin(); it != m_tasks.end(); it++) {
		qDebug() << it->first;
		tasks.append(it->second->toJson());
	}
	jsonObject.insert("tasks", tasks);
	qDebug() << "QJsonObject da lista";
	return jsonObject;
}


std::string List::getName() const { return m_name; }

unsigned short List::getId() const { return _id; }

void List::setName(const std::string & p_name) { m_name = p_name; }

std::vector<std::pair<unsigned short, TaskType>> List::getTasksIds() const {
	std::vector<std::pair<unsigned short, TaskType>> tasksIds;
	for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it) {
		tasksIds.push_back(std::pair<unsigned short, TaskType>(it->first, it->second->getType()));
	}
	return tasksIds;
}


void List::addTask(AbsTask * p_task) {  
    p_task->setList(this);
	m_tasks.insert(std::pair<unsigned short, AbsTask*>(p_task->getId(),p_task));
}

void List::setAsDirectTask(const unsigned short idTask) {
    m_tasksOrder.push_back(idTask);
}

void List::removeTask(const unsigned short idTask) {
    AbsTask* t = m_tasks.at(idTask);
    t->setList(nullptr);
    if(!t->getParent())
		for(auto i = m_tasksOrder.begin(); i < m_tasksOrder.end(); ++i)
            if (*i == idTask) {
                m_tasksOrder.erase(i);
                i = m_tasksOrder.end();
            }
    m_tasks.erase(idTask);
}

void List::deleteTask(const unsigned short idTask) {
    AbsTask* t = getTask(idTask);
    if(t->getParent())
        dynamic_cast<TaskContainer*>(t->getParent())->removeChild(t);
    removeTask(idTask);
    delete t;
}

void List::aggiornaMap(AbsTask *p_task) {
    // essendo che il task "convertito" mantiene l'id, lo si sfrutta per eliminare dal map
    // il pair con il puntatore alla versione non convertita e poi si aggiunge quello nuovo
    m_tasks.erase(p_task->getId());
    addTask(p_task);
}

void List::insertTask(const unsigned short idTask, const unsigned short Posizione) {
	if(!Posizione) {
        m_tasksOrder.insert(m_tasksOrder.begin(),idTask);
	} else {
		for(auto i = m_tasksOrder.begin(); i < m_tasksOrder.end(); i++) {
            if (*i == Posizione) {
                m_tasksOrder.insert(i,idTask);
                i = m_tasksOrder.end();
            }
		}
	}
}

AbsTask *List::getTask(const unsigned short idTask) {
	return m_tasks.at(idTask);
}

void List::setTaskName(const unsigned short taskId, const std::string &newTaskName) {
	m_tasks.at(taskId)->setLabel(newTaskName);
}

