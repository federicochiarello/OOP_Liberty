#ifndef ABSPROJECT_H
#define ABSPROJECT_H

#include <string>
#include <vector>
#include <QDateTime>

#include <QJsonDocument>
#include <QJsonArray>

#include "abstask.h"
#include "list.h"

class AbsProject {
private:
    std::string                             m_name;
    std::vector<List*>                      m_lists;

    // Old
    // std::vector<AbsTask*>								m_tasks;
    // std::map<std::string, std::vector<AbsTask*>>			m_lists;

public:
                                            AbsProject(std::string p_name = std::string());
                                            //Project(const Project& p_pro);
                                            //Project(QJsonDocument& p_doc);


    virtual                                 ~AbsProject();

    void                                    ConvertToPriority(const unsigned int indL, const unsigned int indT);

    void                                    addList(List* p_list);
    void                                    removeList(List* p_list);

    std::string                             getName() const;
    std::vector<List*>                      getLists() const;
    // QJsonDocument                               toJson() const;

    // metodi utilizzati
    List*                                   getList(const unsigned int indL) const;
    void                                    addNewTask(const unsigned int indL, AbsTask* p_task);
    void                                    addNewList();
    void                                    setName(const std::string& p_name);
    void                                    setListName(const unsigned int indL, const std::string& p_name);
};

#endif // ABSPROJECT_H

#ifndef PROJECT_H
#define PROJECT_H

class Project : public AbsProject {


public:

    void                                        ConvertToPriority(const unsigned int indL, const unsigned int indT) override;
};


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
