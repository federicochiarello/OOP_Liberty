#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include <map>
#include <QDateTime>
#include <QVariant>

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
//  void                                    addNewTask(const unsigned short int idList, AbsTask* p_task);
    unsigned short int                      addNewTask(const unsigned short int idList);
    unsigned short int                      addNewTask(const unsigned short int idList, const unsigned short int idTist);
//  void                                    addNewList();
    unsigned short int                      addNewList();
    void                                    setName(const std::string& p_name);
    void                                    setListName(const unsigned short int idList, const std::string& p_name);

    QStringList                             getTaskInfo(const unsigned short int idList, const unsigned short int idTask) const;
    void                                    aggiornaTask(const unsigned short int idList, const unsigned short int idTask, const QStringList info);

//  void                                    convertToPriority(const unsigned short int idList, const unsigned short int idTask);
//  void                                    convertToContainer(const unsigned short int idList, const unsigned short int idTask);
    unsigned short int                      convertToPriority(const unsigned short int idList, const unsigned short int idTask);
    unsigned short int                      convertToContainer(const unsigned short int idList, const unsigned short int idTask);

    void    dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione);
};

#endif // PROJECT_H
