#include "controller.h"

Controller::Controller(Model* m, QObject *parent) : QObject(parent), /* vista(nullptr), */ model(m) {

/*
    connect(VistaDiPartenza, SIGNAL(requestSetActiveProject(const unsigned int)), this, SLOT(setActiveProject(const unsigned int)));
    connect(VistaDiPartenza, SIGNAL(requestDeleteProject(const unsigned int)), this, SLOT(deleteProject(const unsigned int)));

    connect(VistaDiPartenza, SIGNAL(requestNewList()), this, SLOT(addNewList()));
    connect(VistaDiPartenza, SIGNAL(requestNewTask(const unsigned int)), this, SLOT(addNewTask(const unsigned int)));

    connect(VistaDiPartenza, SIGNAL(requestChangePName(const std::string)), this, SLOT(setProjectName(const std::string)));
    connect(VistaDiPartenza, SIGNAL(requestChangeLName(const unsigned int,const std::string)), this, SLOT(setListName(const unsigned int,const std::string)));

    connect(VistaDiPartenza, SIGNAL(convertToPriority(const unsigned int,const unsigned int)), this, SLOT(convertToPrio(const unsigned int, const unsigned int)));
*/
}

void Controller::setActiveProject(const unsigned int indP) {
    model->setActiveProject(indP);
}

void Controller::deleteProject(const unsigned int indP) {
    model->deleteProject(indP);
}

void Controller::addNewList() {
    model->addNewList();
}

void Controller::addNewTask(const unsigned int indL) {
    model->addNewTask(indL);
}

void Controller::setProjectName(const std::string p_name) {
    model->setActiveProjName(p_name);
}

void Controller::setListName(const unsigned int indL, const std::string p_name) {
    model->setListName(indL,p_name);
}

void Controller::convertToPrio(const unsigned int indL, const unsigned int indT) {
    model->ConvertToPriority(indL,indT);
}

/*
void Controller::setView(Vista *v) {
    view = v;
}
*/
