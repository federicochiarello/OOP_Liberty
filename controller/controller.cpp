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

//	connect(VistaDiPartenza, SIGNAL(requestShowTask(const unsigned int,const std::string)), this, SLOT(showTask(const unsigned int,const std::string)));
//	connect(VistaDiPartenza, SIGNAL(requestAggTask(const unsigned int,const std::string,const QStringList)), this, SLOT(aggiornaTask(const unsigned int,const std::string,const QStringList)));


}

void Controller::setView(View* view) {
	_view = view;
}

void Controller::onAppStart() {
	getExistingProjects();
}

void Controller::createNewProject(const std::string& p_name) {
    _model->createNewProject(p_name);
}

void Controller::setActiveProject(const unsigned short indP) {
	 _model->setActiveProject(indP);
}

void Controller::closeProject(const unsigned short indP) {
    _model->closeProject(indP);
}

void Controller::addNewList() {
    _model->addNewList();
    //_view->getLastListId(_model->addNewList());
}

void Controller::addNewTask(const unsigned short idList) {
    _model->addNewTask(idList);
    //_view->getLastTaskId(List,_model->addNewTask(idList));
}

void Controller::addTaskChild(const unsigned short idList, const unsigned short idTask) {
    unsigned short tParent = _model->verifyContainer(idList,idTask);
    unsigned short tChild = _model->addNewTaskChild(idList,tParent);

    // necessario settare nella vista sia l'id del nuovo task (tChild) che l'id del task padre che potrebbe
    // essere stato cambiato se non era un TaskContainer (tParent)

    // ......
}

void Controller::setProjectName(const std::string& p_name) {
	_model->setActiveProjName(p_name);
}

void Controller::setListName(const unsigned short idList, const std::string& p_name) {
    _model->setListName(idList,p_name);
}

void Controller::changeListOrder(const unsigned short listToMove, const unsigned short Posizione) {
    _model->changeListOrder(listToMove,Posizione);
}

void Controller::convertToPrio(const unsigned short idList, const unsigned short idTask) {
    // ritorna l'id del nuovo task "convertito"
    // se il task non necessitava della conversione ritorna 0
    _model->convertToPriority(idList,idTask);
    //_view->aggId(_model->convertToPriority(idList,idTask));
}

void Controller::convertToCont(const unsigned short idList, const unsigned short idTask) {
    // ritorna l'id del nuovo task "convertito"
    // se il task non necessitava della conversione ritorna 0
    _model->convertToContainer(idList,idTask);
    //_view->aggId(_model->convertToContainer(idList,idTask));
}

void Controller::getTaskName(const unsigned short idList, const unsigned short idTask) const {
    // ritorna un std::string
    _model->getTaskName(idList,idTask);
}

void Controller::getTaskPriority(const unsigned short idList, const unsigned short idTask) const {
    // ritorna un QDateTime
    _model->getTaskPriority(idList,idTask);
}

void Controller::getTaskInfo(const unsigned short idList, const unsigned short idTask) const {
    //_view->visualizzaTask(_model->getTaskInfo(idList,idTask));
}

void Controller::aggiornaTask(const unsigned short idList, const unsigned short idTask, const QStringList info) {
    _model->aggiornaTask(idList,idTask,info);
}

void Controller::dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione){
    _model->dragAndDrop(LPartenza,LArrivo,idTask,Posizione);
    //_view->aggiorna vista????????????????????
}

void Controller::getExistingProjects() {

//	QStandardPaths::displayName(QStandardPaths::AppDataLocation)
	QDir projectsDir(QDir::homePath()+"/Documents/Universita/P2");
	QStringList projects = projectsDir.entryList(QDir::Files, QDir::Time);

	projects.prepend(projectsDir.absolutePath());

	emit sendExistingProjects(projects);
}

void Controller::onOpenProject(const QString& path) {
	_model->load(path);
	emit sendProjectInfo(_model->getProjectInfo());
}

void Controller::saveProject(const unsigned short idProject) {
	_model->save(idProject);
}

void Controller::onGetLists(const unsigned short projectId) {
	emit sendListsIds(projectId, _model->getLists(projectId));
}

void Controller::onGetListName(const unsigned short projectId, const unsigned short listId) {

	emit sendListName(projectId, listId, _model->getListName(projectId, listId));
}

//Illegal characters for files " \ / : | < > * ?
