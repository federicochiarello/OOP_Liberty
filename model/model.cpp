#include "model.h"

std::string Model::path = /*QStandardPaths::AppDataLocation*/ "";

Model::Model() :
	m_projects(),
	m_activeProject(nullptr) {}

Model::~Model() {
    if(! m_projects.empty())
        for(auto i=m_projects.begin(); i != m_projects.end(); i++)
            delete i->second;
    //m_projects.clear();
}

void Model::createNewProject(const std::string& p_name) {    
    Project* p = new Project(p_name);
	m_projects.insert(std::pair<unsigned short, Project*>(p->getId(),p));
    m_activeProject = p;
}

void Model::setActiveProject(Project *project) {
	m_activeProject = project;
}

void Model::setActiveProject(const unsigned short idProj) {
    m_projects.at(idProj);
}

void Model::closeProject(const unsigned short idProj) {
    Project* p = m_projects.at(idProj);
	if (m_activeProject == p) {
        m_activeProject = nullptr;
	}
//	save(idProj);
    m_projects.erase(idProj);
    delete p;
}

unsigned short Model::addNewList(const unsigned short projectId) {
	return m_projects.at(projectId)->addNewList();
}

unsigned short Model::addNewTask(const unsigned short projectId, const unsigned short idList) {
    return m_projects.at(projectId)->addNewTask(idList);
}

unsigned short Model::addNewTaskChild(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) {
    return m_projects.at(projectId)->addNewTask(idList,idTask);
}

void Model::setProjectName(const unsigned short projectId, const std::string& p_name) {
	m_projects.at(projectId)->setName(p_name);
}

QString Model::getListName(const unsigned short projectId, const unsigned short listId) const {
	return m_projects.at(projectId)->getListName(listId);
}

void Model::setListName(const unsigned short projectId,const unsigned short idList, const std::string& p_name) {
	m_projects.at(projectId)->setListName(idList,p_name);
}

void Model::changeListOrder(const unsigned short projectId, const unsigned short listToMove, const unsigned short Posizione) {
    m_projects.at(projectId)->changeListOrder(listToMove,Posizione);
}

std::string Model::getProjectName(const unsigned short projectId) const {
    return m_projects.at(projectId)->getName();
}

std::vector<unsigned short> Model::getLists(const unsigned short projectId) const {
	return m_projects.at(projectId)->getLists();
}

QStringList Model::getTaskInfo(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) const {
	return m_projects.at(projectId)->getTaskInfo(idList,idTask);
}

std::string Model::getTaskName(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) const {
	return m_projects.at(projectId)->getTaskName(idList,idTask);
}

std::vector<std::pair<unsigned short, TaskType> > Model::getTasksIds(const unsigned short projectId, const unsigned short listId) const {
	return m_projects.at(projectId)->getTasksIds(listId);
}

QDateTime Model::getTaskPriority(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) const {
    return m_projects.at(projectId)->getTaskPriority(idList,idTask);
}

void Model::aggiornaTask(const unsigned short projectId, const unsigned short idList, const unsigned short idTask, const QStringList info) {
    m_projects.at(projectId)->aggiornaTask(idList,idTask,info);
}

unsigned short Model::convertToPriority(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) {
    return m_projects.at(projectId)->convertToPriority(idList,idTask);
}

unsigned short Model::convertToContainer(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) {
    return m_projects.at(projectId)->convertToContainer(idList,idTask);
}

unsigned short Model::verifyContainer(const unsigned short projectId, const unsigned short idList, const unsigned short idTask) {
    return m_projects.at(projectId)->verifyContainer(idList,idTask);
}

void Model::dragAndDrop(const unsigned short projectId, const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione) {
    m_projects.at(projectId)->dragAndDrop(LPartenza,LArrivo,idTask,Posizione);
}

void Model::load(const QString& filename) {
	qDebug() << filename;
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly)){
		QJsonDocument document = QJsonDocument::fromJson(file.readAll());
		qDebug() << "File opened";
		if (document.isObject()) {
			Project* tmp = new Project(document.object());
			m_projects.insert(std::pair<unsigned short,Project*>(tmp->getId(), tmp));
			setActiveProject(tmp);
		}
	}
	file.close();
}

void Model::save(const unsigned short projectId) const {
	QFile file(QString::fromStdString(path+m_projects.at(projectId)->getName()));
	if (file.open(QIODevice::WriteOnly)) {
		file.write(QJsonDocument(m_activeProject->object()).toJson());
	}
	file.close();
}

std::pair<unsigned short, std::string> Model::getProjectInfo(const unsigned short projectId) {

	Project* project = (projectId ? m_projects.at(projectId) : m_activeProject);

	return std::pair<unsigned short, std::string>(project->getId(), project->getName());
}
