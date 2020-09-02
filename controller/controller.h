
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QDir>
#include <QFile>
#include <QStringList>
#include <QObject>
#include <QStandardPaths>

#include "src/globalenums.h"
#include "model/model.h"

#include <QDebug>

class View;

class Controller : public QObject {
	Q_OBJECT

	View* _view;
	Model* _model;

	bool isValidName(const QString& projectName);

	static QDir projectsDir;

public:
	explicit Controller(Model* m, QObject *parent = nullptr);

	void setView(View* view);
	QString             stuffing(const QString&) const;
	QString             deStuffing(const QString&) const;

signals:

	void sendProjectsDir(const QDir&);
	void sendExistingProjects(const QStringList& projectsNames);
	void sendProjectInfo(std::pair<unsigned short, QString> projectInfo);
	void sendListId(const unsigned short projectId, const unsigned short listId);
	void sendListsIds(const unsigned short projectId, std::vector<unsigned short> listsIds);
	void sendListName(const unsigned short listId, const QString& listName);
	void sendTaskId(const unsigned short listId, const std::pair<unsigned short, TaskType>& taskId);
	void sendTasksIds(const unsigned short listId, const std::vector<std::pair<unsigned short, TaskType>>& tasksIds);
	void sendTaskName(const unsigned short taskId, const QString& taskName);
	void sendTaskInfo(const unsigned short taskId, const QStringList& taskInfo);
	void projectNameValid();
	void projectNameNotValid();
	void setProjectName(const unsigned short projectId, const QString& projectName);
	void setListName(const unsigned short listId, const QString& listName);
	void sendNewTasksList(const unsigned short newListId, const std::pair<unsigned short, TaskType>& taskId);
	void sendDeleteTaskFromList(const unsigned short listId, const unsigned short taskId);
	void updateTaskPreviewName(const unsigned short taskId, const QString& newTaskName);
	void moveTask(const unsigned short taskId);
	void moveList(const unsigned short projectId, const unsigned short listId, const Direction& moveDirection);
	void removeTask(const unsigned short listId, const unsigned short taskId);
	void duplicatedTask(const unsigned short listId, const unsigned short duplicatedTaskId);

public slots:

	void		onAppStart();
	void		onGetProjectsDir();
	void        getExistingProjects();
	void        onOpenProject(const QString& path);
	void		onImportProject(const QString& path);
	void		onExportProject(const unsigned short projectId, const QString& exportPath);
	void		onGetLists(const unsigned short projectId);
	void		onGetListName(const unsigned short projectId, const unsigned short listId);
	void		onGetTasksIds(const unsigned short projectId, const unsigned short listId);
	void		onGetTaskName(const unsigned short projectId, const unsigned short listId, const unsigned short taskId);

	void		onOpenTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId);
	void        onAddNewList(const unsigned short projectId);

	void		onProjectNameChanged(const unsigned short projectId, const QString& newProjectName);
	void		onListNameChanged(const unsigned short projectId, const unsigned short listId, const QString& newListName);

	void		onNewProject(const QString& projectName);
	void        createNewProject(const std::string& = std::string()); // forse da sostituire a onNewProject(), da decidere se avere finestra per il nome e se averla in controller o in view (probabilmente meglio)

	void		onMoveTask(const unsigned short projectId, const unsigned short listId, const std::pair<unsigned short, TaskType>& taskId, const Direction& moveDirection);
	void		onTaskNameChanged(const unsigned short projectId, const unsigned short listId, const unsigned short taskId, const QString& newTaskName);
	void		onUpdateTaskPreviewName(const unsigned short taskId, const QString& newTaskName);

	void		onMoveList(const unsigned short projectId, const unsigned short listId, const Direction& moveDirection);

	void		onDeleteTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId);
	void		onDuplicateTask(const unsigned short projecId, const unsigned short listId, const unsigned short taskId);

	void        setActiveProject(const unsigned short projectId);
	void        closeProject(const unsigned short projectId);

	void        addTaskChild(const unsigned short projectId, const unsigned short idList, const unsigned short idTask);

	void        onNewTask(const unsigned short projectId, const unsigned short idList);

//    void        setProjectName(const std::string& p_name);
//    void        setListName(const unsigned short idList, const std::string& p_name);
	bool        changeListOrder(const unsigned short projectId, const unsigned short listToMove, const Direction& moveDirection);

	void        convertToPrio(const unsigned short projectId, const unsigned short idList, const unsigned short idTask);
	void        convertToCont(const unsigned short projectId, const unsigned short idList, const unsigned short idTask);

//    void        getTaskName(const unsigned short idList, const unsigned short idTask) const;
	void        getTaskPriority(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) const;
	void        getTaskInfo(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) const;
	void        aggiornaTask(const unsigned short projectId, const unsigned short idList, const unsigned short idTask, const QStringList);

	void        dragAndDrop(const unsigned short projectId, const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione =0);

	void		onSaveProject(const unsigned short idProject =0);
	void		onSaveAllProjects();


};

#endif // CONTROLLER_H
