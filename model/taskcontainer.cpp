#include "taskcontainer.h"
#include "taskprioritycontainer.h"
#include "list.h"

TaskContainer::TaskContainer(const std::string p_label, const std::string p_desc, List* p_list, AbsTask* p_parent) :
	AbsTask(p_label,p_desc,p_list,p_parent) {}

TaskContainer::TaskContainer(const QJsonObject& object, std::map<unsigned short,unsigned short>& idsMap, std::map<unsigned short, std::vector<unsigned short>>& childsMap) :
	AbsTask(object, idsMap),
	m_child(std::vector<AbsTask*>()) {

	std::vector<unsigned short> childsIds;
	for (auto childId : object.value("tasksIds").toArray()) {
		childsIds.push_back(childId.toInt());
	}
	childsMap.insert(std::pair<unsigned short, std::vector<unsigned short>>(_id, childsIds));
    qDebug() << "TaskContainer creato";
}

TaskContainer::TaskContainer(const unsigned short id, const std::string p_label, const std::string p_desc) :
    AbsTask(id,p_label,p_desc) {}

TaskContainer::TaskContainer(const TaskContainer & p_task) :
	AbsTask(p_task),
	m_child(p_task.m_child) {}

TaskContainer *TaskContainer::clone() const { return new TaskContainer(*this); }

QJsonObject TaskContainer::toJson() const {
	QJsonObject taskContainerObject = AbsTask::toJson();

	taskContainerObject.insert("taskType", 2);

	QJsonArray childrenIds;

	for (auto child : m_child) {
		childrenIds.append(QJsonValue(child->getId()));
	}

	taskContainerObject.insert("childrenTasks", childrenIds);

	return taskContainerObject;
}

void TaskContainer::setList(List *p_list) {
    List* oldL = getList();
    if(!p_list)
        for(auto i = m_child.begin(); i < m_child.end(); i++)
            oldL->removeTask((*i)->getId());
    else
        for(auto i = m_child.begin(); i < m_child.end(); i++)
            p_list->addTask(*i);

    this->AbsTask::setList(p_list);
}

QStringList TaskContainer::getTaskInfo() const {
    QStringList tmp;
	tmp.push_back("TASK_CONTAINER");
    tmp = tmp + AbsTask::getTaskInfo();
    for(auto i = m_child.begin(); i != m_child.end(); i++)
        tmp.push_back(QVariant((*i)->getId()).toString());
    return tmp;
}

AbsTask *TaskContainer::convertToContainer() const { return nullptr; }

AbsTask *TaskContainer::convertToPriority() const {
    TaskPriorityContainer* t = new TaskPriorityContainer(getId(),getLabel(),getDesc());
    t->addChildList(getChilds());
	return t;
}

TaskType TaskContainer::getType() const {
	return TASK_CONTAINER;
}

std::vector<AbsTask *> TaskContainer::getChilds() const {
    return m_child;
}

void TaskContainer::addChild(AbsTask * p_child) {
    p_child->setParent(this);
    m_child.push_back(p_child);
}

void TaskContainer::removeChild(AbsTask * p_child) {
    for(auto i = m_child.begin(); i < m_child.end(); i++)
        if (*i == p_child) {
            p_child->setParent(nullptr);
            m_child.erase(i);
            i = m_child.end();
        }
}

void TaskContainer::addChildList(std::vector<AbsTask *> p_child) {
    m_child = p_child;
}

void TaskContainer::updateChild(AbsTask *tOld, AbsTask *tNew) {
    removeChild(tOld);
    addChild(tNew);
}
