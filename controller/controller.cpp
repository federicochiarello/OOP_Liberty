#include "controller.h"
#include "view/view.h"

QDir Controller::projectsDir = QDir("../Liberty/projects");//
//QDir(QStandardPaths::displayName(QStandardPaths::AppDataLocation)

bool Controller::isValidName(const QString &projectName) {
	QString illegal=".,<>:\"|?*";
	for (auto character : projectName) {
		if (illegal.contains(character)) {
			return false;
		}
	}
	return true;
}

Controller::Controller(Model* m, QObject *parent) :
	QObject(parent),
	_view(nullptr),
	_model(m) {}

void Controller::setView(View* view) {
	_view = view;
}

QString Controller::stuffing(const QString & p_string) const {
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

QString Controller::deStuffing(const QString & p_string) const {
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

void Controller::onGetProjectsDir() {
	emit sendProjectsDir(projectsDir);
}

void Controller::createNewProject(const std::string& p_name) {
	_model->createNewProject(p_name);
}

void Controller::onMoveTask(const unsigned short projectId, const unsigned short listId, const std::pair<unsigned short, TaskType>& taskId, const Direction& moveDirection) {
	const unsigned short newListId = _model->moveTask(projectId, listId, taskId.first, moveDirection);

    if (newListId) {
		emit moveTask(taskId.first);
		emit sendDeleteTaskFromList(listId, taskId.first);
		emit sendNewTasksList(newListId, taskId);
	}
}

void Controller::onTaskNameChanged(const unsigned short projectId, const unsigned short listId, const unsigned short taskId, const QString &newTaskName) {
	_model->setTaskName(projectId, listId, taskId, newTaskName.toStdString());
}

void Controller::onUpdateTaskPreviewName(const unsigned short taskId, const QString& newTaskName) {
	emit updateTaskPreviewName(taskId, newTaskName);
}

void Controller::onMoveList(const unsigned short projectId, const unsigned short listId, const Direction &moveDirection) {
	if (_model->changeListOrder(projectId, listId, moveDirection)) {
		emit moveList(projectId, listId, moveDirection);
	} else {
		// unable to move list
	}
}

void Controller::onDeleteTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) {
	_model->deleteTask(projectId, listId, taskId);
	emit removeTask(listId, taskId);
}

void Controller::onDuplicateTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) {
//	emit duplicatedTask(listId, _model->duplicateTask(projectId, listId, taskId));
}

void Controller::setActiveProject(const unsigned short projectId) {
	 _model->setActiveProject(projectId);
}

void Controller::closeProject(const unsigned short projectId) {
	_model->closeProject(projectId);
}
void Controller::onNewTask(const unsigned short projectId, const unsigned short listId) {
	emit sendTaskId(listId, std::pair<unsigned short, TaskType>(_model->addNewTask(projectId, listId), TASK));
}

void Controller::addTaskChild(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) {
    _model->convertToContainer(projectId,idList,idTask);
    unsigned short tChild = _model->addNewTaskChild(projectId,idList,idTask);

    // AGGIUNGERE ID FIGLIO ALLA VISTA
}

bool Controller::changeListOrder(const unsigned short projectId, const unsigned short listToMove, const Direction& moveDirection) {
	 return _model->changeListOrder(projectId,listToMove,moveDirection);
 }

void Controller::convertToPrio(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) {
	_model->convertToPriority(projectId,idList,idTask);
}

void Controller::convertToCont(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) {
    _model->convertToContainer(projectId,idList,idTask);
}

void Controller::cloneTask(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) {
    unsigned short cloneId = _model->cloneTask(projectId,idList,idTask);
    // da inserire come ultimo elemento di idList
}

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

	QStringList projects = projectsDir.entryList(QDir::Files, QDir::Time);

	projects.prepend(projectsDir.absolutePath());

	emit sendExistingProjects(projects);
}

void Controller::onOpenProject(const QString& path) {

	QJsonDocument document;
	QFile file(path);
	if (file.open(QIODevice::ReadOnly)){
		document = QJsonDocument::fromJson(file.readAll());
	}
	file.close();
	_model->load(document);
	auto projectInfo = _model->getProjectInfo();
	emit sendProjectInfo(std::pair<unsigned short, QString>(projectInfo.first, QString::fromStdString(projectInfo.second)));
}

void Controller::onImportProject(const QString& path) {
	QString filename = path.mid(path.lastIndexOf("/"));
	QString importedFileNewPath(projectsDir.absolutePath()+"/"+filename);
	if (!QFile::copy(path, importedFileNewPath)) {
//		Segnalare esistenza del progetto con nome uguale
	} else {
		onOpenProject(importedFileNewPath);
	}
}

void Controller::onExportProject(const unsigned short projectId, const QString& exportPath) {
	QFile exportFile(exportPath);
	if (exportFile.exists()) {
//		File già esistente
	} else {
		if (exportFile.open(QIODevice::WriteOnly)) {
			exportFile.write(_model->save(projectId).toBinaryData());
		}
	}
	exportFile.close();
}

void Controller::onSaveProject(const unsigned short projectId) {
	QFile file(projectsDir.absolutePath()+"/"+QString::fromStdString(_model->getProjectName(projectId))+".json");
	if (file.open(QIODevice::WriteOnly)) {
		file.write(_model->save(projectId).toBinaryData());
	}
	file.close();
}

void Controller::onSaveAllProjects() {

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
	if (isValidName(newProjectName)) {
		_model->setProjectName(projectId, stuffing(newProjectName).toStdString());
	} else {
		emit setProjectName(projectId, deStuffing(QString::fromStdString(_model->getProjectName(projectId))));
	}
}

void Controller::onListNameChanged(const unsigned short projectId, const unsigned short listId, const QString &newListName) {
	_model->setListName(projectId, listId, stuffing(newListName).toStdString());
}

void Controller::onNewProject(const QString& projectName) {

	if (isValidName(projectName)) {
		_model->createNewProject(projectName.toStdString());
		auto projectInfo = _model->getProjectInfo();
		emit projectNameValid();
		emit sendProjectInfo(std::pair<unsigned short, QString>(projectInfo.first, QString::fromStdString(projectInfo.second)));
	} else {
		emit projectNameNotValid();
	}
}

//Illegal characters for files " \ / : | < > * ?
