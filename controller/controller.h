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
    void        addNewTask(const unsigned short int idList);
    void        addTaskChild(const unsigned short int idList, const unsigned short int idTask);

    void        setProjectName(const std::string& p_name);
    void        setListName(const unsigned short int idList, const std::string& p_name);

    void        convertToPrio(const unsigned short int idList, const unsigned short int idTask);
    void        convertToCont(const unsigned short int idList, const unsigned short int idTask);

    void        showTask(const unsigned short int idList, const unsigned short int idTask) const;
    void        aggiornaTask(const unsigned short int idList, const unsigned short int idTask, const QStringList);

    void        dragAndDrop(const unsigned short int LPartenza, const unsigned short int LArrivo, const unsigned short int idTask, const unsigned short int Posizione =0);

    void        getExistingProjects();
    void        openProject(QString);
};

#endif // CONTROLLER_H
