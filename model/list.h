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

// Dichiarazione Incompleta
class AbsTask;

class List {
private:
	unsigned short int                      _id;
    std::string                             m_name;
    std::map<unsigned short int,AbsTask*>   m_tasks;
    std::vector<unsigned short int>         m_tasksOrder;   //contiene i task figli diretti della lista ordinati

    static unsigned short int               nextID;

public:
											explicit List(const std::string name =std::string());
											explicit List(unsigned short id, const std::string name =std::string());
											explicit List(const QJsonObject& object);
                                            List(const List& p_list);
                                            ~List();

    std::string                             getName() const;
    unsigned short int                      getId() const;
    void                                    setName(const std::string& p_name);

    void                                    addTask(AbsTask* p_task);
    void                                    removeTask(const unsigned short int idTask);
    void                                    updateTask(const unsigned short int idTask, AbsTask* p_task);
    void                                    insertTask(const unsigned short int Posizione,const unsigned short int idTask);
    void                                    setAsDirectTask(const unsigned short int idTask);
    AbsTask*                                getTask(const unsigned short int idTask);

	List* fromJsonObject(QJsonObject object);
};

#endif // LIST_H
