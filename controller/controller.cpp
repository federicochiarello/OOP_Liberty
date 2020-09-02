#include "controller.h"
#include "view/view.h"

bool Controller::isValidProjectName(const QString &projectName) {
	QString illegal=".,<>:\"|?*";
	for (auto character : projectName) {
		if (illegal.contains(character)) {
			return false;
		}
	}
	return true;
}

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

QString Controller::stuffing(const QString & p_string) {
    QString backSlash, stuffed;
    int j = 0;
    for(int i = 0; i < p_string.size(); i++) {
        if(p_string[i] == QChar('\\')) {
            backSlash.insert(j,QString("\\\\"));
            j++;
        } else
            backSlash[j] = p_string[i];
        j++;
    }
    j = 0;
    for(int i = 0; i < backSlash.size(); i++) {
        if(backSlash[i] == QChar('"')) {
            stuffed.insert(j,QString("\\\""));
            j++;
        } else if(backSlash[i] == QChar('\n')) {
            stuffed.insert(j,QString("\\n"));
            j++;
        } else if(backSlash[i] == QChar('\t')) {
            stuffed.insert(j,QString("\\t"));
            j++;
        } else if(backSlash[i] == QChar('\b')) {
            stuffed.insert(j,QString("\\b"));
            j++;
        } else if(backSlash[i] == QChar('\r')) {
            stuffed.insert(j,QString("\\r"));
            j++;
        } else if(backSlash[i] == QChar('\f')) {
            stuffed.insert(j,QString("\\f"));
            j++;
        } else
            stuffed[j] = backSlash[i];
        j++;
    }
    return stuffed;
}

QString Controller::deStuffing(const QString & p_string) {
    QString deStuffed;
    for(int i = 0; i < p_string.size(); i++)
        if(p_string[i] == QChar('\\')) {
            if(p_string[i+1] == QChar('\\')) {
                deStuffed.push_back('\\');
                i++;
            } else if(p_string[i+1] == QChar('"')) {
                deStuffed.push_back('"');
                i++;
            } else if(p_string[i+1] == QChar('n')) {
                deStuffed.push_back('\n');
                i++;
            } else if(p_string[i+1] == QChar('t')) {
                deStuffed.push_back('\t');
                i++;
            } else if(p_string[i+1] == QChar('b')) {
                deStuffed.push_back('\b');
                i++;
            } else if(p_string[i+1] == QChar('r')) {
                deStuffed.push_back('\r');
                i++;
            } else if(p_string[i+1] == QChar('f')) {
                deStuffed.push_back('\f');
                i++;
            } else
                deStuffed.push_back(p_string[i]);
        } else
            deStuffed.push_back(p_string[i]);
    return deStuffed;
}

void Controller::onAppStart() {
	getExistingProjects();
}

void Controller::createNewProject(const std::string& p_name) {
    _model->createNewProject(p_name);
}

void Controller::setActiveProject(const unsigned short projectId) {
     _model->setActiveProject(projectId);
}

void Controller::closeProject(const unsigned short projectId) {
    _model->closeProject(projectId);
}

//void Controller::addNewList() {
//    _model->addNewList();
//    //_view->getLastListId(_model->addNewList());
//}

void Controller::addNewTask(const unsigned short projectId, const unsigned short idList) {
    _model->addNewTask(projectId,idList);
    //_view->getLastTaskId(List,_model->addNewTask(idList));
}

void Controller::addTaskChild(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) {
    unsigned short tParent = _model->verifyContainer(projectId,idList,idTask);
    unsigned short tChild = _model->addNewTaskChild(projectId,idList,tParent);

    // necessario settare nella vista sia l'id del nuovo task (tChild) che l'id del task padre che potrebbe
    // essere stato cambiato se non era un TaskContainer (tParent)

    // ......
}

//void Controller::setProjectName(const std::string& p_name) {
//	_model->setActiveProjName(p_name);
//}

//void Controller::setListName(const unsigned short idList, const std::string& p_name) {
//    _model->setListName(idList,p_name);
//}

bool Controller::changeListOrder(const unsigned short projectId, const unsigned short listToMove, const Direction& moveDirection) {
    return _model->changeListOrder(projectId,listToMove,moveDirection);
}

void Controller::convertToPrio(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) {
    // ritorna l'id del nuovo task "convertito"
    // se il task non necessitava della conversione ritorna 0
    _model->convertToPriority(projectId,idList,idTask);
    //_view->aggId(_model->convertToPriority(idList,idTask));
}

void Controller::convertToCont(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) {
    // ritorna l'id del nuovo task "convertito"
    // se il task non necessitava della conversione ritorna 0
    _model->convertToContainer(projectId,idList,idTask);
    //_view->aggId(_model->convertToContainer(idList,idTask));
}

//void Controller::getTaskName(const unsigned short idList, const unsigned short idTask) const {
//    // ritorna un std::string
//    _model->getTaskName(idList,idTask);
//}

void Controller::getTaskPriority(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) const {
    // ritorna un QDateTime
    _model->getTaskPriority(projectId,idList,idTask);
}

void Controller::getTaskInfo(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) const {
    //_view->visualizzaTask(_model->getTaskInfo(projectId,idList,idTask));
}

void Controller::aggiornaTask(const unsigned short projectId, const unsigned short idList, const unsigned short idTask, const QStringList info) {
    _model->aggiornaTask(projectId,idList,idTask,info);
}

void Controller::dragAndDrop(const unsigned short projectId, const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione){
    _model->dragAndDrop(projectId,LPartenza,LArrivo,idTask,Posizione);
    //_view->aggiorna vista????????????????????
}

void Controller::getExistingProjects() {

//	QStandardPaths::displayName(QStandardPaths::AppDataLocation)
    QDir projectsDir(QDir::homePath()+"/Documents/Universita/P2");

    QStringList projects = projectsDir.entryList(QDir::Files,QDir::Time);

	projects.prepend(projectsDir.absolutePath());

	emit sendExistingProjects(projects);
}

void Controller::onOpenProject(const QString& path) {
	_model->load(path);
	qDebug() << "Model loaded";
	auto projectInfo = _model->getProjectInfo();
	emit sendProjectInfo(std::pair<unsigned short, QString>(projectInfo.first, QString::fromStdString(projectInfo.second)));
}

void Controller::saveProject(const unsigned short idProject) {
	_model->save(idProject);
}

void Controller::onGetLists(const unsigned short projectId) {
	emit sendListsIds(projectId, _model->getLists(projectId));
}

void Controller::onGetListName(const unsigned short projectId, const unsigned short listId) {

	emit sendListName(listId, _model->getListName(projectId, listId));
}

void Controller::onGetTasksIds(const unsigned short projectId, const unsigned short listId) {
	emit sendTasksIds(listId, _model->getTasksIds(projectId, listId));
}

void Controller::onGetTaskName(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) {
	emit sendTaskName(taskId, QString::fromStdString(_model->getTaskName(projectId, listId, taskId)));
}

void Controller::onOpenTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) {
	emit sendTaskInfo(taskId, _model->getTaskInfo(projectId, listId, taskId));
}

void Controller::onAddNewList(const unsigned short projectId) {
	emit sendListId(projectId, _model->addNewList(projectId));
}

void Controller::onProjectNameChanged(const unsigned short projectId, const QString& newProjectName) {
//	Controllare che sia un nome valido e stuffing
//	if (validName()) {
	_model->setProjectName(projectId, newProjectName.toStdString());
	//	} else { emit setProjectName(projectId, QString::fromStdString(_model->getProjectName(projectId))); }inutile aggiornare la lista a meno che il nome no vada bene (mettere vecchio nome)
}

void Controller::onListNameChanged(const unsigned short projectId, const unsigned short listId, const QString &newListName) {
//	Controllare che sia un nome valido e stuffing
//	if (validName()) {
	_model->setListName(projectId, listId, newListName.toStdString());
//	} else { emit setListName(listId, QString::fromStdString(_model->getListName(projectId, listId))); }inutile aggiornare la lista a meno che il nome no vada bene (mettere vecchio nome)
}

void Controller::onNewProject(const QString& projectName) {

	if (isValidProjectName(projectName)) {
		_model->createNewProject(projectName.toStdString());
		auto projectInfo = _model->getProjectInfo();
		emit projectNameValid();
		emit sendProjectInfo(std::pair<unsigned short, QString>(projectInfo.first, QString::fromStdString(projectInfo.second)));
	} else {
		emit projectNameNotValid();
	}
}

//Illegal characters for files " \ / : | < > * ?
