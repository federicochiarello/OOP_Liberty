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
    std::string                         m_basePath;
    std::map<unsigned short,Project*>   m_projects;
    Project*                            m_activeProject;
public:
	Model(const std::string path =std::string());
    ~Model();


    void                createNewProject(const std::string& p_name);
    void                setActiveProject(const unsigned short idProj);
    void                closeProject(const unsigned short idProj);

    unsigned short      addNewList();
    unsigned short      addNewTask(const unsigned short idList);
    unsigned short      addNewTaskChild(const unsigned short idList, const unsigned short idTask);

    void                setActiveProjName(const std::string& p_name);
    void                setListName(const unsigned short idList, const std::string& p_name);
    void                changeListOrder(const unsigned short listToMove, const unsigned short Posizione);


    QStringList         getTaskInfo(const unsigned short idList, const unsigned short idTask) const;
    void                aggiornaTask(const unsigned short idList, const unsigned short idTask, const QStringList info);

    unsigned short      convertToPriority(const unsigned short idList, const unsigned short idTask);
    unsigned short      convertToContainer(const unsigned short idList, const unsigned short idTask);
    unsigned short      verifyContainer(const unsigned short idList, const unsigned short idTask);

    void    dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione);

	void	load(const std::string& filename);
	void	save() const;

};

#endif // MODEL_H
