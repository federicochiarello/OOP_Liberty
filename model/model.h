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
    Model(const std::string path);
    ~Model();


    void    createNewProject(const std::string& p_name);
    void    setActiveProject(const unsigned int indP);
    void    deleteProject(const unsigned int indP);

    void    addNewList();
    void    addNewTask(const unsigned short int idList);

    void    setActiveProjName(const std::string& p_name);
    void    setListName(const unsigned short int idList, const std::string& p_name);


    void    convertToPriority(const unsigned short int idList, const unsigned short int idTask);
    void    convertToContainer(const unsigned short int idList, const unsigned short int idTask);

};

#endif // MODEL_H
