#include "taskprioritycontainer.h"

#include <QDebug>

TaskPriorityContainer::TaskPriorityContainer(const std::string p_label, const std::string p_desc, List *p_list, AbsTask *p_parent, QDateTime p_priority)
	: AbsTask(p_label,p_desc,p_list,p_parent), TaskContainer(p_label,p_desc,p_list,p_parent), TaskPriority(p_label,p_desc,p_list,p_parent,p_priority) {}

TaskPriorityContainer::TaskPriorityContainer(const QJsonObject& object, std::map<unsigned short,unsigned short>& idsMap, std::map<unsigned short, std::vector<unsigned short>>& childsMap) :
	AbsTask(object, idsMap),
	TaskContainer(object, idsMap, childsMap),
	TaskPriority(object, idsMap) {
	qDebug() << "TaskPriorityContainer creato";
}

TaskPriorityContainer *TaskPriorityContainer::clone() const { return new TaskPriorityContainer(*this); }

QJsonObject TaskPriorityContainer::toJson() const {
	QJsonObject jsonObject = AbsTask::toJson();

	jsonObject.insert("taskType", 4);
	jsonObject.insert("taskPriority", m_priority.toString(dateTimeFormat));

	QJsonArray childrenIds;
	for (auto task : m_child) {
		childrenIds.append(task->getId());
	}

	jsonObject.insert("childrenTasks", childrenIds);

	return jsonObject;
}

void TaskPriorityContainer::setPriority(QDateTime p_priority) {
    this->TaskPriority::setPriority(p_priority);
    std::vector<AbsTask*> tmp = this->getChilds();
    for(auto i = tmp.begin(); i != tmp.end(); i++) {
        TaskPriority* p = dynamic_cast<TaskPriority*>(*i);
        if( p && p->getPriority() >= p_priority )
            p->setPriority(p_priority);
    }
}

QStringList TaskPriorityContainer::getTaskInfo() const {
    QStringList tmp;
	tmp.push_back("TASK_PRIORITY_CONTAINER");
    tmp = tmp + AbsTask::getTaskInfo();
    tmp.push_back(getPriority().toString(AbsTask::dateTimeFormat));
    for(auto i = m_child.begin(); i != m_child.end(); i++)
        tmp.push_back(QVariant((*i)->getId()).toString());
    return tmp;
}

AbsTask *TaskPriorityContainer::convertToContainer() const { return nullptr; }

AbsTask *TaskPriorityContainer::convertToPriority() const { return nullptr; }

TaskType TaskPriorityContainer::getType() const {
	return TASK_PRIORITY_CONTAINER;
}
