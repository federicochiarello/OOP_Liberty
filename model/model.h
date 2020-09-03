#ifndef MODEL_H
#define MODEL_H

#include <QFile>
#include <QJsonDocument>
#include "veqtor.h"

#include "project.h"
#include "list.h"
#include "abstask.h"
#include "task.h"
#include "taskcontainer.h"
#include "taskpriority.h"
#include "taskprioritycontainer.h"

class Model {
private:
//  std::string                         m_basePath;
    std::map<unsigned short,Project*>   m_projects;
    Project*                            m_activeProject;

    void                                setActiveProject(Project* project);

    static std::string                  path;

public:
	Model();
    ~Model();

	void                createNewProject(const std::string& p_name =std::string());
    void                setActiveProject(const unsigned short projectId);
    void                closeProject(const unsigned short projectId);

	unsigned short      addNewList(const unsigned short projectId);
    unsigned short      addNewTask(const unsigned short projectId, const unsigned short listId);
    unsigned short      addNewTaskChild(const unsigned short projectId, const unsigned short listId, const unsigned short taskId);

    void                setProjectName(const unsigned short projectId, const std::string& p_name);
    void                setListName(const unsigned short projectId, const unsigned short listId, const std::string& p_name);
	void				setTaskName(const unsigned short projectId, const unsigned short listId, const unsigned short taskId, const std::string& newTaskName);
	bool                changeListOrder(const unsigned short projectId, const unsigned short listToMove, const Direction& moveDirection);

    std::string         getProjectName(const unsigned short projectId) const;
    veqtor<unsigned short> getLists(const unsigned short projectId) const;
	QString				getListName(const unsigned short projectId, const unsigned short listId) const;
    QStringList         getTaskInfo(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) const;
    std::string         getTaskName(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) const;
    veqtor<std::pair<unsigned short, TaskType>> getTasksIds(const unsigned short projectId, const unsigned short listId) const;
    QDateTime           getTaskPriority(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) const;

    void                aggiornaTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId, const QStringList info);
    void                deleteTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId);

    void                convertToPriority(const unsigned short projectId, const unsigned short listId, const unsigned short taskId);
    void                convertToContainer(const unsigned short projectId, const unsigned short listId, const unsigned short taskId);
    unsigned short      cloneTask(const unsigned short projectId, const unsigned short idList, const unsigned short idTask);

    void                dragAndDrop(const unsigned short projectId, const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short taskId, const unsigned short Posizione);
    unsigned short      moveTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId, const Direction& moveDirection);
    bool                VmoveTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId, const VDirection& moveDirection);


    void                load(const QJsonDocument& document);
    QJsonDocument       save(const unsigned short projectId);

	std::pair<unsigned short, std::string> getProjectInfo(const unsigned short projectId =0);
	// se projectId =0 allora si richiedono le info di activeProject

};

#endif // MODEL_H
