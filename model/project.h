#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include <map>
#include <QDateTime>

//#include <QJsonDocument>
//#include <QJsonArray>

#include "abstask.h"
#include "list.h"

class Project {
private:
    std::string                             m_name;
    std::map<unsigned short int,List*>      m_lists;
    std::vector<unsigned short int>         m_listOrder;

    //std::vector<List*>                      m_lists;

    // Old
    // std::vector<AbsTask*>								m_tasks;
    // std::map<std::string, std::vector<AbsTask*>>			m_lists;

public:
                                            Project(std::string p_name = std::string());
                                            //Project(const Project& p_pro);
                                            //Project(QJsonDocument& p_doc);

                                            ~Project();

    //void                                    ConvertToPriority(const unsigned int indL, const unsigned int indT);

    void                                    addList(List* p_list);
    void                                    removeList(List* p_list);

    std::string                             getName() const;
    std::vector<List*>                      getLists() const;
    // QJsonDocument                        toJson() const;

    // metodi utilizzati
    List*                                   getList(const unsigned short int idList) const;
    void                                    addNewTask(const unsigned int indL, AbsTask* p_task);
    void                                    addNewList();
    void                                    setName(const std::string& p_name);
    void                                    setListName(const unsigned short int idL, const std::string& p_name);
};

#endif // PROJECT_H
