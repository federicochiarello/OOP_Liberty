#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QDir>
#include <QFile>
#include <QStringList>
#include <QObject>
#include <QStandardPaths>

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
	void sendProjectInfo(const std::pair<unsigned short, QString>&);
	void sendListsIds(const unsigned short projectId, std::vector<const unsigned short> listsIds);

public slots:

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

    void        showTask(const unsigned short idList, const unsigned short idTask) const;
    void        aggiornaTask(const unsigned short idList, const unsigned short idTask, const QStringList);

    void        dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione =0);

    void        getExistingProjects();
	void        openProject(const QString);
	void		saveProject(const unsigned short idProject);

	void		onGetLists(const unsigned short projectId);
};

#endif // CONTROLLER_H
