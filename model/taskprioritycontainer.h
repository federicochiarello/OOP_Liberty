#ifndef TASKPRIORITYCONTAINER_H
#define TASKPRIORITYCONTAINER_H

#include "taskcontainer.h"
#include "taskpriority.h"

class TaskPriorityContainer : public TaskContainer, public TaskPriority {
public:
	explicit TaskPriorityContainer(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr, QDateTime p_priority =QDateTime());
    explicit TaskPriorityContainer(const unsigned short id, const std::string p_label =std::string(), const std::string p_desc =std::string());
    explicit TaskPriorityContainer(const QJsonObject& object, std::map<unsigned short,unsigned short>& idsMap, std::map<unsigned short, veqtor<unsigned short>>& childsMap);

    TaskPriorityContainer*                  clone() const override;
    QJsonObject                             toJson() const override;
    void                                    setPriority(QDateTime p_priority) override;
    QStringList                             getTaskInfo() const override;
    AbsTask*                                convertToContainer() const override;
    AbsTask*                                convertToPriority() const override;
	TaskType								getType() const override;
};

#endif // TASKPRIORITYCONTAINER_H
