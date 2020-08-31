#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QDir>
#include <QFile>
#include <QStringList>
#include <QObject>
#include <QStandardPaths>

#include "src/globalenums.h"
#include "model/model.h"

class View;

class Controller : public QObject {
	Q_OBJECT

	View* _view;
	Model* _model;

public:
	explicit Controller(Model* m, QObject *parent = nullptr);

	void setView(View* view);

signals:

	void sendExistingProjects(const QStringList&);
    void sendProjectInfo(const std::pair<unsigned short, const QString&>&);
    void sendListsIds(const unsigned short, const std::vector<unsigned short>);
	void sendListName(const unsigned short, const unsigned short, const QString&);
    void sendTasksIds(const unsigned short, const unsigned short, const std::vector<std::pair<unsigned short, const TaskType&>>);
	void sendTaskName(const unsigned short, const unsigned short, const unsigned short, const QString&);

public slots:

	void		onAppStart();

	void        getExistingProjects();
	void        onOpenProject(const QString& path);
	void		onGetLists(const unsigned short projectId);
	void		onGetListName(const unsigned short projectId, const unsigned short listId);
	void		onGetTasksIds(const unsigned short projectId, const unsigned short listId);
	void		onGetTaskName(const unsigned short projectId, const unsigned short listId, const unsigned short taskId);

	void        createNewProject(const std::string& = std::string());
    void        setActiveProject(const unsigned short indP);
    void        closeProject(const unsigned short indP);

	void        addNewList();
    void        addNewTask(const unsigned short idList);
    void        addTaskChild(const unsigned short idList, const unsigned short idTask);

    void        setProjectName(const std::string& p_name);
    void        setListName(const unsigned short idList, const std::string& p_name);
    void        changeListOrder(const unsigned short listToMove, const unsigned short Posizione);

    void        convertToPrio(const unsigned short idList, const unsigned short idTask);
    void        convertToCont(const unsigned short idList, const unsigned short idTask);

    void        getTaskName(const unsigned short idList, const unsigned short idTask) const;
    void        getTaskPriority(const unsigned short idList, const unsigned short idTask) const;
    void        getTaskInfo(const unsigned short idList, const unsigned short idTask) const;
    void        aggiornaTask(const unsigned short idList, const unsigned short idTask, const QStringList);

    void        dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione =0);

	void		saveProject(const unsigned short idProject);


};

#endif // CONTROLLER_H
