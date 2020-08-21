#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <typeinfo>

//#include <QJsonDocument>
//#include <QJsonArray>

#include "abstask.h"
#include "absproject.h"
#include "taskcontainer.h"
#include "taskpriority.h"
#include "taskprioritycontainer.h"

template <class T>
class Project : public AbsProject {
private:
    //const std::type_info&						m_priorityType;

public:
                                                Project(const std::string p_name =std::string());
                                                //Project(const Project& p_pro);
                                                //Project(QJsonDocument& p_doc);

    // QJsonDocument                               toJson() const;

    void                                        ConvertToPriority(const unsigned int indL, const unsigned int indT) override;

    // bool                                        dynamicCastTemplate(AbsTask* p_task);
};

// m_priorityType(typeid (T))
template<class T>
Project<T>::Project(const std::string p_name) : AbsProject(p_name) {}


template<class T>
void Project<T>::ConvertToPriority(const unsigned int indL, const unsigned int indT) {
    List* l = getList(indL);
    AbsTask* tmp = l->getTask(indT);
    if(dynamic_cast<TaskContainer*>(tmp))
        tmp = new TaskPriorityContainer<T>(tmp->getLabel(),tmp->getDesc(),tmp->getList(),tmp->getParent());
    else
        tmp = new TaskPriority<T>(tmp->getLabel(),tmp->getDesc(),tmp->getList(),tmp->getParent());
    l->updateTask(indT,tmp);
}

#endif // PROJECT_H
