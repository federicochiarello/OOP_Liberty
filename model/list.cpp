#include "list.h"
#include <iostream>

unsigned short List::nextID = 0;

List::List(unsigned short id, const std::string name) :		_id(id),
															m_name(name),
															m_tasks(std::map<unsigned short, AbsTask*>()),
															m_tasksOrder(std::vector<unsigned short>()) {
	if (id > nextID) nextID = id;
}

List::List(const std::string p_name) :		_id(++nextID),
											m_name(p_name),
											m_tasks(std::map<unsigned short, AbsTask*>()),
											m_tasksOrder(std::vector<unsigned short>()) {}

List::List(const QJsonObject& object, std::vector<AbsTask*>& tasks, std::map<unsigned short, unsigned short>& idsMap) :	_id(++nextID),
									m_name(object.value("listName").toString().toStdString()),
									m_tasks(std::map<unsigned short, AbsTask*>()),
									m_tasksOrder(std::vector<unsigned short>()) {

	for (const QJsonValue task : object.value("tasks").toArray()) {
		AbsTask* tmp = nullptr;
		switch(task.toObject().value("taskType").toInt()) {
			case 1:
				tmp = new Task(task.toObject(), idsMap);
				break;
			case 2:
				tmp = new TaskContainer(task.toObject(), idsMap);
				break;
			case 3:
				tmp = new TaskPriority(task.toObject(), idsMap);
				break;
			case 4:
				tmp = new TaskPriorityContainer(task.toObject(), idsMap);
				break;
		}
		if (tmp) {
			m_tasks.insert(std::pair<unsigned short, AbsTask*>(tmp->getId(), tmp));
			tasks.push_back(tmp);
			m_tasksOrder.push_back(tmp->getId());
		}
	}
}

List::List(const List &p_list) :	_id(++nextID),
									m_name(p_list.m_name),
									m_tasks(p_list.m_tasks),
									m_tasksOrder(p_list.m_tasksOrder) {}

List::~List() {
    if(! m_tasks.empty())
        for(std::map<unsigned short,AbsTask*>::iterator i=m_tasks.begin(); i!=m_tasks.end(); i++)
            delete i->second;
}

QJsonObject List::toJson() const {
	QJsonObject jsonObject;

//	jsonObject.insert("listId", _id);
	jsonObject.insert("listName", QString::fromStdString(m_name));

	QJsonArray tasks;
	for (auto it = m_tasks.begin(); it != m_tasks.end(); it++) {
		tasks.append(it->second->toJson());
	}
	jsonObject.insert("tasks", tasks);

	return jsonObject;
}


std::string List::getName() const { return m_name; }

unsigned short List::getId() const { return _id; }

void List::setName(const std::string & p_name) { m_name = p_name; }

void List::addTask(AbsTask * p_task) {
    p_task->setList(this);
    std::map<unsigned short,AbsTask*>::value_type t(p_task->getId(),p_task);
    m_tasks.insert(t);
}

void List::setAsDirectTask(const unsigned short idTask) {
    m_tasksOrder.push_back(idTask);
}

void List::removeTask(const unsigned short idTask) {
    AbsTask* t = m_tasks.at(idTask);
    t->setList(nullptr);
    if(!t->getParent())
        for(std::vector<unsigned short>::iterator i = m_tasksOrder.begin(); i < m_tasksOrder.end(); i++)
            if (*i == idTask) {
                m_tasksOrder.erase(i);
                i = m_tasksOrder.end();
            }
    m_tasks.erase(idTask);
}

void List::updateTask(const unsigned short idTask, AbsTask *p_task) {
    if(!m_tasks.at(idTask)->getParent()) {
        for(std::vector<unsigned short>::iterator i = m_tasksOrder.begin(); i < m_tasksOrder.end(); ++i)
            if (*i == idTask) {
                *i = p_task->getId();
                i = m_tasksOrder.end();
            }
    }
    m_tasks.erase(idTask);
    addTask(p_task);
}

void List::insertTask(const unsigned short idTask, const unsigned short Posizione) {
    if(!Posizione)
        m_tasksOrder.insert(m_tasksOrder.begin(),idTask);
    else
        for(std::vector<unsigned short>::iterator i = m_tasksOrder.begin(); i < m_tasksOrder.end(); i++)
            if (*i == Posizione) {
                m_tasksOrder.insert(i,idTask);
                i = m_tasksOrder.end();
            }
}

AbsTask *List::getTask(const unsigned short idTask) {
	return m_tasks.at(idTask);
}

List *List::fromJsonObject(QJsonObject object) {

}

