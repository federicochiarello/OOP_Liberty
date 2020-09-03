#include "taskpriority.h"
#include "taskprioritycontainer.h"

#include <QDebug>

TaskPriority::TaskPriority(const std::string p_label, const std::string p_desc, List *p_list, AbsTask *p_parent,QDateTime p_priority)
    :   AbsTask(p_label,p_desc,p_list,p_parent), m_priority(p_priority) {}

TaskPriority::TaskPriority(const unsigned short id, const std::string p_label, const std::string p_desc)
    :   AbsTask(id,p_label,p_desc) {}

TaskPriority::TaskPriority(const QJsonObject& object, std::map<unsigned short,unsigned short>& idsMap) :
	AbsTask(object, idsMap),
	m_priority(QDateTime::fromString(object.value("taskPriority").toString(), dateTimeFormat)) {
	qDebug() << "TaskPriority creato";
}

TaskPriority *TaskPriority::clone() const {
	return new TaskPriority(*this);
}

QJsonObject TaskPriority::toJson() const {
	QJsonObject taskPriorityObject = AbsTask::toJson();

	taskPriorityObject.insert("taskType", 3);
	taskPriorityObject.insert("taskPriority", m_priority.toString(dateTimeFormat));
	qDebug() << "obj da TaskPriority";
	return taskPriorityObject;
}

void TaskPriority::aggiornaTask(const QStringList info) {
    setLabel(info[0].toStdString());
    setDesc(info[1].toStdString());
    setPriority(QDateTime::fromString(info[2],AbsTask::dateTimeFormat));
}

QStringList TaskPriority::getTaskInfo() const {
    QStringList tmp;
	tmp.push_back("TASK_PRIORITY");
    tmp = tmp + AbsTask::getTaskInfo();
    tmp.push_back(getPriority().toString(AbsTask::dateTimeFormat));
    return tmp;
}

AbsTask *TaskPriority::convertToContainer() const {
    TaskPriorityContainer* t = new TaskPriorityContainer(getId(),getLabel(),getDesc());
    t->setPriority(getPriority());
    return t;
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
