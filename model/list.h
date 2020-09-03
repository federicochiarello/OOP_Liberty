#ifndef LIST_H
#define LIST_H

#include <string>
#include <map>
#include "veqtor.h"

#include <QJsonObject>
#include <QJsonArray>

#include "abstask.h"
#include "task.h"
#include "taskcontainer.h"
#include "taskpriority.h"
#include "taskprioritycontainer.h"

#include <QDebug>

class AbsTask;

class List {
private:
    const unsigned short                    _id;
    std::string                             m_name;
    std::map<unsigned short,AbsTask*>       m_tasks;
    veqtor<unsigned short>                  m_tasksOrder;

    // m_tasks contiene <id,puntatore> ai task contenuti nella lista
    // m_taskOrder contiene la lista dei task di primo livello ordinati

    static unsigned short               nextID;

public:
											explicit List(const std::string& name =std::string());
											explicit List(const unsigned short id, const std::string& name =std::string());
                                            explicit List(const QJsonObject& object, veqtor<AbsTask*>& tasks, std::map<unsigned short,unsigned short>& idsMap, std::map<unsigned short, veqtor<unsigned short>>& childsMap);
                                            List(const List& p_list);
                                            ~List();

    QJsonObject                             toJson() const;
    std::string                             getName() const;
    unsigned short                          getId() const;
    void                                    setName(const std::string& p_name);

    veqtor<std::pair<unsigned short, TaskType>> getTasksIds() const;
    void                                    addTask(AbsTask* p_task);
    void                                    removeTask(const unsigned short taskId);
    void                                    deleteTask(const unsigned short taskId);
    void                                    aggiornaMap(AbsTask* p_task);
    void                                    insertTask(const unsigned short Posizione,const unsigned short taskId);
    void                                    setAsDirectTask(const unsigned short taskId);
    AbsTask*                                getTask(const unsigned short taskId);
	void									setTaskName(const unsigned short taskId, const std::string& newTaskName);
    bool                                    VmoveTask(const unsigned short taskId, const VDirection &moveDirection);

};

#endif // LIST_H
