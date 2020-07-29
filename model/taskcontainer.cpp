#include "taskcontainer.h"

TaskContainer::TaskContainer(const std::string p_label, const std::string p_desc, AbsTask *p_parent, std::string *p_list)
    : AbsTask(p_label,p_desc,p_parent,p_list), AbsTaskContainer(p_label,p_desc,p_parent,p_list) {}
