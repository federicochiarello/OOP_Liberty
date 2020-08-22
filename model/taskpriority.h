#ifndef TASKPRIORITY_H
#define TASKPRIORITY_H

#include "abstask.h"
#include <QDateTime>

class TaskPriority : virtual public AbsTask {
private:

    QDateTime                       m_priority;

public:

    TaskPriority(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr, QDateTime p_priority =QDateTime());

    TaskPriority*                   clone() const override;

    QDateTime                       getPriority() const;

    virtual void                    setPriority(QDateTime p_priority);

};

#endif // TASKPRIORITY_H
