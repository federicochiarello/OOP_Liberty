#include "controller.h"

Controller::Controller(Model* m, QObject *parent) : QObject(parent), view(nullptr), model(m) {

//	connect(VistaDiPartenza, SIGNAL(requestNewProject()), this, SLOT(createNewProject()));

//	connect(VistaDiPartenza, SIGNAL(requestSetActiveProject(const unsigned int)), this, SLOT(setActiveProject(const unsigned int)));
//	connect(VistaDiPartenza, SIGNAL(requestDeleteProject(const unsigned int)), this, SLOT(deleteProject(const unsigned int)));

//	connect(VistaDiPartenza, SIGNAL(requestNewList()), this, SLOT(addNewList()));
//	connect(VistaDiPartenza, SIGNAL(requestNewTask(const unsigned int)), this, SLOT(addNewTask(const unsigned int)));

//	connect(VistaDiPartenza, SIGNAL(requestChangePName(const std::string)), this, SLOT(setProjectName(const std::string)));
//	connect(VistaDiPartenza, SIGNAL(requestChangeLName(const unsigned int,const std::string)), this, SLOT(setListName(const unsigned int,const std::string)));

//	connect(VistaDiPartenza, SIGNAL(convertToPriority(const unsigned int,const unsigned int)), this, SLOT(convertToPrio(const unsigned int, const unsigned int)));

}

void Controller::setView(View* p_view) {
    view = p_view;
}

void Controller::createNewProject(){
    model->createNewProject();
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

void Controller::addNewTask(const unsigned short int idList) {
    model->addNewTask(idList);
}

void Controller::setProjectName(const std::string p_name) {
    model->setActiveProjName(p_name);
}

void Controller::setListName(const unsigned short int idList, const std::string p_name) {
    model->setListName(idList,p_name);
}

void Controller::convertToPrio(const unsigned short int idList, const unsigned short int idTask) {
    model->ConvertToPriority(idList,idTask);
}


































