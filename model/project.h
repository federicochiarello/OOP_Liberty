#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <map>
#include <QDateTime>
#include <QJsonArray>
#include <QVariant>
#include "veqtor.h"

#include "list.h"
#include "abstask.h"
#include "task.h"
#include "taskcontainer.h"
#include "taskpriority.h"
#include "taskprioritycontainer.h"

class Project {

    const unsigned short                _id;
    std::string                         m_name;
    std::map<unsigned short,List*>      m_lists;
    veqtor<unsigned short>         m_listsOrder;
	bool _modified;

	static unsigned short               nextID;

public:
                                    explicit Project(std::string p_name = std::string());
                                    Project(const QJsonObject& object);
                                    ~Project();

    void                            addList(List* p_list);
    void                            removeList(unsigned short listId);

    unsigned short                  getId() const;
    std::string                     getName() const;
    veqtor<unsigned short>		getLists() const;
    QJsonObject						object();
    Project*						fromJson(const QJsonObject& object);

    unsigned short                  addNewTask(const unsigned short listId);
    unsigned short                  addNewTask(const unsigned short listId, const unsigned short taskId);
    AbsTask*                        getPointer(const unsigned short listId, const unsigned short taskId) const;
    unsigned short                  addNewList();

    void                            setName(const std::string& p_name);
    QString							getListName(const unsigned short listId) const;
    void                            setListName(const unsigned short listId, const std::string& p_name);
    void							setTaskName(const unsigned short listId, const unsigned short taskId, const std::string& newTaskName);
    bool                            changeListOrder(const unsigned short listToMove, const Direction& moveDirection);

    veqtor<std::pair<unsigned short, TaskType>> getTasksIds(const unsigned short listId) const;
    QStringList                     getTaskInfo(const unsigned short listId, const unsigned short taskId) const;
    std::string                     getTaskName(const unsigned short listId, const unsigned short taskId) const;
    QDateTime                       getTaskPriority(const unsigned short listId, const unsigned short taskId) const;
    void                            aggiornaTask(const unsigned short listId, const unsigned short taskId, const QStringList info);
    void                            deleteTask(const unsigned short listId, const unsigned short taskId);
    unsigned short                  cloneTask(const unsigned short listId, const unsigned short taskId);


    void                            convertToPriority(const unsigned short listId, const unsigned short taskId);
    void                            convertToContainer(const unsigned short listId, const unsigned short taskId);

    void            dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short taskId, const unsigned short Posizione);
    unsigned short  moveTask(const unsigned short listId, const unsigned short taskId, const Direction &moveDirection);
    bool            VmoveTask(const unsigned short listId, const unsigned short taskId, const VDirection &moveDirection);

};

#endif // PROJECT_H
