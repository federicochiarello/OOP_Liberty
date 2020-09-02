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

	bool isValidProjectName(const QString& projectName);
public:
	explicit Controller(Model* m, QObject *parent = nullptr);

	void setView(View* view);
    QString             stuffing(const QString&);
    QString             deStuffing(const QString&);

signals:

	void sendExistingProjects(const QStringList& projectsNames);
	void sendProjectInfo(std::pair<unsigned short, QString> projectInfo);
	void sendListId(const unsigned short projectId, const unsigned short listId);
	void sendListsIds(const unsigned short projectId, std::vector<unsigned short> listsIds);
	void sendListName(const unsigned short listId, const QString& listName);
	void sendTasksIds(const unsigned short listId, const std::vector<std::pair<unsigned short, TaskType>>& tasksIds);
	void sendTaskName(const unsigned short taskId, const QString& taskName);
	void sendTaskInfo(const unsigned short taskId, const QStringList& taskInfo);
	void projectNameValid();
	void projectNameNotValid();
	void setProjectName(const unsigned short projectId, const QString& projectName);
	void setListName(const unsigned short listId, const QString& listName);

public slots:

	void		onAppStart();

	void        getExistingProjects();
	void        onOpenProject(const QString& path);
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

    void        setActiveProject(const unsigned short projectId);
    void        closeProject(const unsigned short projectId);

    void        addNewTask(const unsigned short projectId, const unsigned short idList);
    void        addTaskChild(const unsigned short projectId, const unsigned short idList, const unsigned short idTask);

//    void        setProjectName(const std::string& p_name);
//    void        setListName(const unsigned short idList, const std::string& p_name);
    void        changeListOrder(const unsigned short projectId, const unsigned short listToMove, const unsigned short Posizione);

    void        convertToPrio(const unsigned short projectId, const unsigned short idList, const unsigned short idTask);
    void        convertToCont(const unsigned short projectId, const unsigned short idList, const unsigned short idTask);

//    void        getTaskName(const unsigned short idList, const unsigned short idTask) const;
    void        getTaskPriority(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) const;
    void        getTaskInfo(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) const;
    void        aggiornaTask(const unsigned short projectId, const unsigned short idList, const unsigned short idTask, const QStringList);

    void        dragAndDrop(const unsigned short projectId, const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione =0);

	void		saveProject(const unsigned short idProject);


};

#endif // CONTROLLER_H
