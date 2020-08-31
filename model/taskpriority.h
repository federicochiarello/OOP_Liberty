#ifndef TASKPRIORITY_H
#define TASKPRIORITY_H

#include "abstask.h"
#include <QDateTime>

class TaskPriority : virtual public AbsTask {
protected:
    QDateTime                       m_priority;

public:
	explicit TaskPriority(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr, QDateTime p_priority =QDateTime());
    explicit TaskPriority(const QJsonObject& object, std::map<unsigned short,unsigned short>& idsMap);

    TaskPriority*                   clone() const override;
    QJsonObject                     toJson() const override;
    void                            aggiornaTask(const QStringList info) override;
    QStringList                     getTaskInfo() const override;
    AbsTask*                        convertToContainer() const override;
    AbsTask*                        convertToPriority() const override;
	TaskType getType() const override;

    QDateTime                       getPriority() const;

    virtual void                    setPriority(QDateTime p_priority);
};

#endif // TASKPRIORITY_H
