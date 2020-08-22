#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
//#include "vista.h"
#include "model.h"

class Controller : public QObject {
    Q_OBJECT
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

private:
    //Vista* view;
    Model* model;

};

#endif // CONTROLLER_H
