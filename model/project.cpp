/*
#include "project.h"

template<class T>
Project<T>::Project(const std::string p_name) : AbsProject(p_name), m_priorityType(typeid (T)) {}

template<class T>
AbsTask* Project<T>::convertToPriority(AbsTask* p_task, T priority) {
    if(dynamic_cast<TaskContainer*>(p_task))
        return new TaskPriorityContainer<T>(priority,p_task->getLabel(),p_task->getDesc(),p_task->getList(),p_task->getParent());
    else
        return new TaskPriority<T>(priority,p_task->getLabel(),p_task->getDesc(),p_task->getList(),p_task->getParent());
}

template<class T>
const std::type_info &Project<T>::getPriorityType() const { return m_priorityType; }


template <class T>
Project<T>::Project(const Project& p_pro) : m_priorityType(typeid (T)) {}


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
