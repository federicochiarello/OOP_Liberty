#include "task.h"
#include "taskcontainer.h"
#include "taskpriority.h"

#include <QDebug>

Task::Task(List *list, AbsTask *parent) :
	AbsTask(list, parent) {}

Task::Task(const std::string p_label, const std::string p_desc, List *p_list, AbsTask *p_parent) :
	AbsTask(p_label,p_desc,p_list,p_parent) {}

Task::Task(const QJsonObject &object, std::map<unsigned short,unsigned short>& idsMap) :
	AbsTask(object, idsMap) {
	qDebug() << "Task creato";
}

Task *Task::clone() const { return new Task(*this); }

QJsonObject Task::toJson() const {
	QJsonObject taskObject = AbsTask::toJson();
	taskObject.insert("taskType", 1);
	qDebug() << "obj da Task";
    return taskObject;
}

QStringList Task::getTaskInfo() const {
    QStringList tmp;
    tmp.push_back("TASK");
    tmp = tmp + AbsTask::getTaskInfo();
    return tmp;
}

AbsTask *Task::convertToContainer() const {
    return new TaskContainer(getId(),getLabel(),getDesc());
}

AbsTask *Task::convertToPriority() const {
    return new TaskPriority(getId(),getLabel(),getDesc());
}

TaskType Task::getType() const {
	return TASK;
}
