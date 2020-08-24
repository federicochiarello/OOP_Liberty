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


// controllare se possibile aggiungere attributo const
signals:
	void sendExistingProjects(QStringList);
public slots:


    //void        createNewProject(); //???????

	void        setActiveProject(const unsigned int indP);
	void        deleteProject(const unsigned int indP);

	void        addNewList();
	void        addNewTask(const unsigned int indL);

	void        setProjectName(const std::string p_name);
	void        setListName(const unsigned int indL, const std::string p_name);


//	void        convertToPrio(const unsigned int indL, const unsigned int indT);

	void getExistingProjects();
	void openProject(QString);
};

#endif // CONTROLLER_H
