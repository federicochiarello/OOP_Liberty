#ifndef MODEL_H
#define MODEL_H

#include "project.h"

// Necessario includerli tutti?
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


    void    setActiveProject(const unsigned int indP);
    void    deleteProject(const unsigned int indP);

    void    addNewList();
    void    addNewTask(const unsigned int indL);

    void    setActiveProjName(const std::string& p_name);
    void    setListName(const unsigned short int idList, const std::string& p_name);


    void    ConvertToPriority(const unsigned int indL, const unsigned int indT);


};

#endif // MODEL_H
