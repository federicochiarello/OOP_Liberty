#include "taskpriority.h"
#include "taskprioritycontainer.h"

TaskPriority::TaskPriority(const std::string p_label, const std::string p_desc, List *p_list, AbsTask *p_parent,QDateTime p_priority)
	:   AbsTask(p_label,p_desc,p_list,p_parent), m_priority(p_priority) {}

TaskPriority::TaskPriority(const QJsonObject& object, std::map<unsigned short,unsigned short>& idsMap) :
	AbsTask(object, idsMap),
	m_priority(QDateTime::fromString(object.value("taskPriority").toString(), dateTimeFormat)) {}


TaskPriority *TaskPriority::clone() const {
	return new TaskPriority(*this);
}

QJsonObject TaskPriority::toJson() const {
	QJsonObject taskPriorityObject = AbsTask::toJson();

	taskPriorityObject.insert("taskType", 3);
	taskPriorityObject.insert("taskPriority", m_priority.toString(dateTimeFormat));

	return taskPriorityObject;
}

void TaskPriority::aggiornaTask(const QStringList info) {
    setLabel(info[0].toStdString());
    setDesc(info[1].toStdString());
    setPriority(QDateTime::fromString(info[2],AbsTask::dateTimeFormat));
}

QStringList TaskPriority::getTaskInfo() const {
    QStringList tmp;
    tmp.push_back("TASKPRIORITY");
    tmp = tmp + AbsTask::getTaskInfo();
    tmp.push_back(getPriority().toString(AbsTask::dateTimeFormat));
    return tmp;
}

AbsTask *TaskPriority::convertToContainer() const {
    return new TaskPriorityContainer(getLabel(),getDesc(),nullptr,nullptr,getPriority());
}

AbsTask *TaskPriority::convertToPriority() const { return nullptr; }

TaskType TaskPriority::getType() const {
	return TASK_PRIORITY;
}

QDateTime TaskPriority::getPriority() const {
    return m_priority;
}

void TaskPriority::setPriority(QDateTime p_priority) {
    m_priority = p_priority;
}
