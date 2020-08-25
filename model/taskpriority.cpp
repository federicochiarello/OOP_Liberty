#include "taskpriority.h"

TaskPriority::TaskPriority(const std::string p_label, const std::string p_desc, List *p_list, AbsTask *p_parent,QDateTime p_priority)
	:   AbsTask(p_label,p_desc,p_list,p_parent), m_priority(p_priority) {}

TaskPriority::TaskPriority(const QJsonObject& object) {

}


TaskPriority *TaskPriority::clone() const {
    return new TaskPriority(*this);
}

QDateTime TaskPriority::getPriority() const {
    return m_priority;
}

void TaskPriority::setPriority(QDateTime p_priority) {
    m_priority = p_priority;
}
