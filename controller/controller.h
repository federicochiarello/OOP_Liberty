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
	void sendExistingProjects(QStringList);

public slots:

    void        createNewProject(const std::string& = std::string());
	void        setActiveProject(const unsigned int indP);
	void        deleteProject(const unsigned int indP);

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
    void        openProject(QString);
};

#endif // CONTROLLER_H
