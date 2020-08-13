#include "task.h"

Task::Task(const std::string p_label, const std::string p_desc, std::string *p_list, AbsTask *p_parent) :
    AbsTask(p_label,p_desc,p_list,p_parent) {}

Task *Task::clone() const { return new Task(*this); }

// Task::Task(const Task& p_task, AbsTask* p_parent) : AbsTask(p_task,p_parent) {}
