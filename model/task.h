#ifndef TASK_H
#define TASK_H

#include "abstask.h"

class Task : public AbsTask {
public:
	explicit Task(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr);
	explicit Task(QJsonObject& object);
	Task* clone() const override;
};

#endif // TASK_H
