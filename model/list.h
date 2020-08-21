#ifndef LIST_H
#define LIST_H

#include <string>
#include <vector>

#include "abstask.h"

// Dichiarazione Incompleta
class AbsTask;

class List {
private:
    std::string                         m_name;
    std::vector<AbsTask*>				m_tasks;
    unsigned short int                  id;

    static unsigned short int           nextID;

public:
                                        List(const std::string name =std::string());
                                        List(const List& p_list);

    std::string							getName() const;
    std::vector<AbsTask*>				getListChildren() const;
    unsigned short int                  getId() const;

    void                                addTask(AbsTask* p_task);
    void                                removeTask(AbsTask* p_task);

    // Metodi utilizzati
    AbsTask*                            getTask(const unsigned int indT) const;
    void                                updateTask(const unsigned int indT, AbsTask* p_task);
    void                                addNewTask(AbsTask* p_task);
    void                                setName(const std::string& p_name);

};

#endif // LIST_H"
