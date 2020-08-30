#ifndef TASK_H
#define TASK_H

#include "abstask.h"

class Task : public AbsTask {
public:
	explicit Task(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr);
	explicit Task(const QJsonObject& object, std::map<unsigned short, unsigned short>& idsMap);

    Task*               clone() const override;
    QJsonObject         toJson() const override;
    QStringList         getTaskInfo() const override;
    AbsTask*            convertToContainer() const override;
    AbsTask*            convertToPriority() const override;
};

#endif // TASK_H
