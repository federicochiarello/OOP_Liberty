#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include <map>
#include <QDateTime>

//#include <QJsonDocument>
#include <QJsonArray>

#include "abstask.h"

#include "task.h"
#include "taskcontainer.h"
#include "taskpriority.h"
#include "taskprioritycontainer.h"

#include "list.h"

class Project {
private:
    std::string                             m_name;
    std::map<unsigned short int,List*>      m_lists;
    std::vector<unsigned short int>         m_listsOrder;

    //std::vector<List*>                      m_lists;

    // Old
    // std::vector<AbsTask*>								m_tasks;
    // std::map<std::string, std::vector<AbsTask*>>			m_lists;

public:
											Project(std::string p_name = std::string());
//											Project(const Project& p_pro);
//											Project(QJsonObject& object);
                                            ~Project();

    void                                    addList(List* p_list);
    void                                    removeList(unsigned short int idList);

	std::string                             getName() const;
//	std::vector<List*>                      getLists() const;
//	QJsonDocument                        toJson() const;
	Project* fromJson(const QJsonObject& object);

    // metodi utilizzati
    void                                    addNewTask(const unsigned short int idList, AbsTask* p_task);
    void                                    addNewList();
    void                                    setName(const std::string& p_name);
    void                                    setListName(const unsigned short int idList, const std::string& p_name);

    void                                    convertToPriority(const unsigned short int idList, const unsigned short int idTask);
    void                                    convertToContainer(const unsigned short int idList, const unsigned short int idTask);
};

#endif // PROJECT_H
