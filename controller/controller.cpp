#include "controller.h"
#include "view/view.h"

Controller::Controller(Model* m, QObject *parent) : QObject(parent), _view(nullptr), _model(m) {

//	connect(VistaDiPartenza, SIGNAL(requestNewProject(const std::string&)), this, SLOT(createNewProject(const std::string&)));
//	connect(VistaDiPartenza, SIGNAL(requestSetActiveProject(const unsigned int)), this, SLOT(setActiveProject(const unsigned int)));
//	connect(VistaDiPartenza, SIGNAL(requestDeleteProject(const unsigned int)), this, SLOT(deleteProject(const unsigned int)));

//	connect(VistaDiPartenza, SIGNAL(requestNewList()), this, SLOT(addNewList()));
//	connect(VistaDiPartenza, SIGNAL(requestNewTask(const unsigned int)), this, SLOT(addNewTask(const unsigned int)));

//	connect(VistaDiPartenza, SIGNAL(requestChangePName(const std::string)), this, SLOT(setProjectName(const std::string)));
//	connect(VistaDiPartenza, SIGNAL(requestChangeLName(const unsigned int,const std::string)), this, SLOT(setListName(const unsigned int,const std::string)));

//	connect(VistaDiPartenza, SIGNAL(convertToPriority(const unsigned short int,const unsigned short int)), this, SLOT(convertToPrio(const unsigned short int, const unsigned short int)));
//  connect(VistaDiPartenza, SIGNAL(convertToContainer(const unsigned short int,const unsigned short int)), this, SLOT(convertToCont(const unsigned short int, const unsigned short int)));

    connect(_view, SIGNAL(appStart()), this, SLOT(getExistingProjects()));
	connect(this, SIGNAL(sendExistingProjects(QStringList)), _view, SLOT());
	connect(_view, SIGNAL(openProject(QString)), this, SLOT(openProject(QString)));
}

void Controller::setView(View* view) {
	_view = view;
}

void Controller::createNewProject(const std::string& p_name) {
    _model->createNewProject(p_name);
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

void Controller::addNewTask(const unsigned short int idList) {
    _model->addNewTask(idList);
}

void Controller::setProjectName(const std::string& p_name) {
	_model->setActiveProjName(p_name);
}

void Controller::setListName(const unsigned short int idList, const std::string& p_name) {
    _model->setListName(idList,p_name);
}

void Controller::convertToPrio(const unsigned short int idList, const unsigned short int idTask) {
    _model->convertToPriority(idList,idTask);
}

void Controller::convertToCont(const unsigned short int idList, const unsigned short int idTask) {
    _model->convertToContainer(idList,idTask);
}

void Controller::getExistingProjects() {

	QDir projectsDir(QStandardPaths::displayName(QStandardPaths::AppDataLocation));
	QStringList projects = projectsDir.entryList(QDir::Files, QDir::Time);

	projects.prepend(projectsDir.dirName());

	emit sendExistingProjects(projects);
}

void Controller::openProject(QString) {
}

//Illegal characters for files " \ / : | < > * ?
