#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include <map>
#include <QDateTime>
#include <QVariant>

#include <QJsonArray>

#include "abstask.h"
#include "task.h"
#include "taskcontainer.h"
#include "taskpriority.h"
#include "taskprioritycontainer.h"

#include "list.h"

class Project {

    unsigned short                      _id;
    std::string                         m_name;
	std::map<unsigned short,List*>      m_lists;
	std::vector<unsigned short>         m_listsOrder;
	bool _modified;

//	std::vector<AbsTask*>								m_tasks;

	static unsigned short               nextID;

//	std::vector<List*>                      m_lists
//	Old

public:
											Project(std::string p_name = std::string());
											Project(const QJsonObject& object);
//											Project(const Project& p_pro);
                                            ~Project();

    void                                    addList(List* p_list);
    void                                    removeList(unsigned short idList);

    unsigned short                          getId() const;
	std::string                             getName() const;
	std::vector<unsigned short>				getLists() const;
	QJsonObject								object();
	Project*								fromJson(const QJsonObject& object);

    unsigned short                          addNewTask(const unsigned short idList);
    unsigned short                          addNewTask(const unsigned short idList, const unsigned short idTask);
    AbsTask*                                getPointer(const unsigned short idList, const unsigned short idTask);
    unsigned short                          addNewList();

    void                                    setName(const std::string& p_name);
	QString									getListName(const unsigned short listId) const;
    void                                    setListName(const unsigned short idList, const std::string& p_name);
    void                                    changeListOrder(const unsigned short listToMove, const unsigned short Posizione);


    QStringList                             getTaskInfo(const unsigned short idList, const unsigned short idTask) const;
    void                                    aggiornaTask(const unsigned short idList, const unsigned short idTask, const QStringList info);
    unsigned short                          verifyContainer(const unsigned short idList, const unsigned short idTask);

    unsigned short                          convertToPriority(const unsigned short idList, const unsigned short idTask);
    unsigned short                          convertToContainer(const unsigned short idList, const unsigned short idTask);

    void    dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione);
};

#endif // PROJECT_H
