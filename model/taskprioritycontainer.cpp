#include "taskprioritycontainer.h"

TaskPriorityContainer::TaskPriorityContainer(const std::string p_label, const std::string p_desc, List *p_list, AbsTask *p_parent, QDateTime p_priority)
	: AbsTask(p_label,p_desc,p_list,p_parent), TaskContainer(p_label,p_desc,p_list,p_parent), TaskPriority(p_label,p_desc,p_list,p_parent,p_priority) {}

TaskPriorityContainer::TaskPriorityContainer(const QJsonObject& object, std::map<unsigned short, unsigned short>& idsMap) :
	AbsTask(object, idsMap),
	TaskContainer(object, idsMap),
	TaskPriority(object, idsMap)
	{}

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
    for(std::vector<AbsTask*>::iterator i = tmp.begin(); i != tmp.end(); i++) {
        TaskPriority* p = dynamic_cast<TaskPriority*>(*i);
        if( p && p->getPriority() >= p_priority )
            p->setPriority(p_priority);
    }
}
