#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "view/view.h"
#include "model/model.h"

class Controller : public QObject {
	Q_OBJECT

	View* _view;
	Model* _model;

public:
	explicit Controller(Model* m, QObject *parent = nullptr);

	//void setView(Vista* v);


// controllare se possibile aggiungere attributo const
public slots:


	void        createNewProject(); //???????

	void        setActiveProject(const unsigned int indP);
	void        deleteProject(const unsigned int indP);

	void        addNewList();
	void        addNewTask(const unsigned int indL);

	void        setProjectName(const std::string p_name);
	void        setListName(const unsigned int indL, const std::string p_name);



	void        convertToPrio(const unsigned int indL, const unsigned int indT);
};

#endif // CONTROLLER_H
