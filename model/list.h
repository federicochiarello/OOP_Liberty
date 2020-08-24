#ifndef LIST_H
#define LIST_H

#include <string>
#include <vector>
#include <map>

#include "abstask.h"

// Dichiarazione Incompleta
class AbsTask;

class List {
private:
    std::string                             m_name;
    std::map<unsigned short int,AbsTask*>   m_tasks;
    std::vector<unsigned short int>         m_tasksOrder;   //contiene i task figli diretti della lista ordinati
    unsigned short int                      id;

    static unsigned short int               nextID;

public:
                                            List(const std::string name =std::string());
                                            List(const List& p_list);
                                            ~List();

    std::string                             getName() const;
    unsigned short int                      getId() const;
    void                                    setName(const std::string& p_name);

    void                                    addTask(AbsTask* p_task);
    void                                    removeTask(const unsigned short int idTask);
    void                                    updateTask(const unsigned short int idTask, AbsTask* p_task);
    void                                    setAsDirectTask(const unsigned short int idTask);
    AbsTask*                                getTask(const unsigned short int idTask);

};

#endif // LIST_H
