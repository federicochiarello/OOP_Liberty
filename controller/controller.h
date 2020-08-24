#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "view/view.h"
#include "model/model.h"

class Controller : public QObject {
	Q_OBJECT

    View* view;
    Model* model;

public:
	explicit Controller(Model* m, QObject *parent = nullptr);

	void setView(View* view);

// controllare se possibile aggiungere attributo const
public slots:


    void        createNewProject();

    void        setActiveProject(const unsigned int indP);
	void        deleteProject(const unsigned int indP);

	void        addNewList();
    void        addNewTask(const unsigned short int idList);

	void        setProjectName(const std::string p_name);
    void        setListName(const unsigned short int idList, const std::string p_name);



    void        convertToPrio(const unsigned short int idList, const unsigned short int idTask);
};

#endif // CONTROLLER_H
