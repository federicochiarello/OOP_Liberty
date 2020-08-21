#ifndef ABSPROJECT_H
#define ABSPROJECT_H

#include <string>
#include <vector>

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

    virtual                                 ~AbsProject() =0;

    virtual void                            ConvertToPriority(const unsigned int indL, const unsigned int indT)=0;

    void                                    addList(List* p_list);
    void                                    removeList(List* p_list);

    std::string                             getName() const;
    std::vector<List*>                      getLists() const;

    // metodi utilizzati
    List*                                   getList(const unsigned int indL) const;
    void                                    addNewTask(const unsigned int indL, AbsTask* p_task);
    void                                    addNewList();
    void                                    setName(const std::string& p_name);
    void                                    setListName(const unsigned int indL, const std::string& p_name);
};

#endif // ABSPROJECT_H
