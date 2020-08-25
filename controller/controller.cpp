#include "controller.h"
#include "view/view.h"

Controller::Controller(Model* m, QObject *parent) : QObject(parent), _view(nullptr), _model(m) {

//	connect(VistaDiPartenza, SIGNAL(requestSetActiveProject(const unsigned int)), this, SLOT(setActiveProject(const unsigned int)));
//	connect(VistaDiPartenza, SIGNAL(requestDeleteProject(const unsigned int)), this, SLOT(deleteProject(const unsigned int)));

//	connect(VistaDiPartenza, SIGNAL(requestNewList()), this, SLOT(addNewList()));
//	connect(VistaDiPartenza, SIGNAL(requestNewTask(const unsigned int)), this, SLOT(addNewTask(const unsigned int)));

//	connect(VistaDiPartenza, SIGNAL(requestChangePName(const std::string)), this, SLOT(setProjectName(const std::string)));
//	connect(VistaDiPartenza, SIGNAL(requestChangeLName(const unsigned int,const std::string)), this, SLOT(setListName(const unsigned int,const std::string)));

//	connect(VistaDiPartenza, SIGNAL(convertToPriority(const unsigned int,const unsigned int)), this, SLOT(convertToPrio(const unsigned int, const unsigned int)));

}

void Controller::setView(View* view) {
	_view = view;
}

void Controller::setActiveProject(const unsigned int indP) {
	 _model->setActiveProject(indP);
}

void Controller::deleteProject(const unsigned int indP) {
	_model->deleteProject(indP);
}

void Controller::addNewList() {
	_model->addNewList();
}

void Controller::addNewTask(const unsigned int indL) {
	_model->addNewTask(indL);
}

void Controller::setProjectName(const std::string p_name) {
	_model->setActiveProjName(p_name);
}

void Controller::setListName(const unsigned int indL, const std::string p_name) {
	_model->setListName(indL,p_name);
}

void Controller::getExistingProjects() {

//	QStandardPaths::displayName(QStandardPaths::AppDataLocation)
	QDir projectsDir(QDir::homePath()+"/Documents/Universita/P2");
	QStringList projects = projectsDir.entryList(QDir::Files, QDir::Time);

	projects.prepend(projectsDir.absolutePath());

	emit sendExistingProjects(projects);
}

void Controller::openProject(QString) {
}

//void Controller::convertToPrio(const unsigned int indL, const unsigned int indT) {
//	_model->ConvertToPriority(indL,indT);
//}

//Illegal characters for files " \ / : | < > * ?
