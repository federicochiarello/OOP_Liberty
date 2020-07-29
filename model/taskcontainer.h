#ifndef TASKCONTAINER_H
#define TASKCONTAINER_H

#include "abstask.h"
#include "abstaskcontainer.h"

class TaskContainer : public AbsTaskContainer {
public:
    TaskContainer(const std::string p_label =std::string(), const std::string p_desc =std::string(), AbsTask* p_parent =nullptr, std::string* p_list =nullptr);
};

#endif // TASKCONTAINER_H
