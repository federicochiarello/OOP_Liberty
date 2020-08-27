#ifndef MODEL_H
#define MODEL_H

#include "project.h"
#include "list.h"
#include "abstask.h"
#include "task.h"
#include "taskcontainer.h"
#include "taskpriority.h"
#include "taskprioritycontainer.h"

#include <vector>

class Model {
private:
	std::string						m_basePath;
    std::vector<Project*>           m_projects;
    Project*						m_activeProject;
public:
	Model(const std::string path =std::string());
    ~Model();


    void                createNewProject(const std::string& p_name);
    void                setActiveProject(const unsigned int indP);
    void                deleteProject(const unsigned int indP);

//  void                addNewList();
    unsigned short int  addNewList();
//  void                addNewTask(const unsigned short int idList);
    unsigned short int  addNewTask(const unsigned short int idList);
    unsigned short int  addNewTaskChild(const unsigned short int idList, const unsigned short int idTask);

    void                setActiveProjName(const std::string& p_name);
    void                setListName(const unsigned short int idList, const std::string& p_name);
    void                changeListOrder(const unsigned short listToMove, const unsigned short Posizione);


    QStringList         getTaskInfo(const unsigned short idList, const unsigned short idTask) const;
    void                aggiornaTask(const unsigned short idList, const unsigned short idTask, const QStringList info);


//  void                convertToPriority(const unsigned short int idList, const unsigned short int idTask);
//  void                convertToContainer(const unsigned short int idList, const unsigned short int idTask);

    unsigned short int  convertToPriority(const unsigned short int idList, const unsigned short int idTask);
    unsigned short int  convertToContainer(const unsigned short int idList, const unsigned short int idTask);

    void    dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione);

	void	load(const std::string& filename);
	void	save() const;

};

#endif // MODEL_H
