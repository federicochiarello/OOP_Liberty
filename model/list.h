#ifndef LIST_H
#define LIST_H

#include <string>
#include <vector>
#include <map>

#include <QJsonObject>
#include <QJsonArray>

#include "abstask.h"
#include "task.h"
#include "taskcontainer.h"
#include "taskpriority.h"
#include "taskprioritycontainer.h"

class AbsTask;

class List {

    const unsigned short                    _id;
    std::string                             m_name;
    std::map<const unsigned short,AbsTask*>       m_tasks;
    std::vector<const unsigned short>             m_tasksOrder;   //contiene i task figli diretti della lista ordinati

    static unsigned short int               nextID;

public:
											explicit List(const std::string name =std::string());
                                            explicit List(const unsigned short id, const std::string name =std::string());
											explicit List(const QJsonObject& object, std::vector<AbsTask*>& tasks, std::map<const unsigned short, const unsigned short>& idsMap);
                                            List(const List& p_list);
                                            ~List();

	QJsonObject toJson() const;
    std::string                             getName() const;
    unsigned short                          getId() const;
    void                                    setName(const std::string& p_name);

    void                                    addTask(AbsTask* p_task);
    void                                    removeTask(const unsigned short idTask);
    void                                    updateTask(const unsigned short idTask, AbsTask* p_task);
    void                                    insertTask(const unsigned short Posizione,const unsigned short idTask);
    void                                    setAsDirectTask(const unsigned short idTask);
    AbsTask*                                getTask(const unsigned short idTask);
};

#endif // LIST_H
