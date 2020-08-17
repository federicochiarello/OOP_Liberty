#include "task.h"

Task::Task(const std::string p_label, const std::string p_desc, List *p_list, AbsTask *p_parent) :
    AbsTask(p_label,p_desc,p_list,p_parent) {}

Task *Task::clone() const { return new Task(*this); }
