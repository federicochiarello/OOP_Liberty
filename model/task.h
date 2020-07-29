#ifndef TASK_H
#define TASK_H

#include "abstask.h"

class Task : public AbsTask {
public:
    Task(const std::string p_label =std::string(), const std::string p_desc =std::string(), AbsTask* p_parent =nullptr, std::string* p_list =nullptr);
    //~Task();
};

#endif // TASK_H
