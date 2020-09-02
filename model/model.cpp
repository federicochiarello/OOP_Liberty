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

void Model::setActiveProject(const unsigned short projectId) {
    m_projects.at(projectId);
}

void Model::closeProject(const unsigned short projectId) {
    Project* p = m_projects.at(projectId);
	if (m_activeProject == p) {
        m_activeProject = nullptr;
	}
//	save(idProj);
    m_projects.erase(projectId);
    delete p;
}

unsigned short Model::addNewList(const unsigned short projectId) {
	return m_projects.at(projectId)->addNewList();
}

unsigned short Model::addNewTask(const unsigned short projectId, const unsigned short listId) {
    return m_projects.at(projectId)->addNewTask(listId);
}

unsigned short Model::addNewTaskChild(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) {
    return m_projects.at(projectId)->addNewTask(listId,taskId);
}

void Model::setProjectName(const unsigned short projectId, const std::string& p_name) {
	m_projects.at(projectId)->setName(p_name);
}

QString Model::getListName(const unsigned short projectId, const unsigned short listId) const {
	return m_projects.at(projectId)->getListName(listId);
}

void Model::setListName(const unsigned short projectId,const unsigned short listId, const std::string& p_name) {
    m_projects.at(projectId)->setListName(listId,p_name);
}

void Model::setTaskName(const unsigned short projectId, const unsigned short listId, const unsigned short taskId, const std::string &newTaskName) {
	m_projects.at(projectId)->setTaskName(listId, taskId, newTaskName);
}

bool Model::changeListOrder(const unsigned short projectId, const unsigned short listToMove, const Direction& moveDirection) {
	 return m_projects.at(projectId)->changeListOrder(listToMove,moveDirection);
}

std::string Model::getProjectName(const unsigned short projectId) const {
	return (projectId?m_projects.at(projectId):m_activeProject)->getName();
}

std::vector<unsigned short> Model::getLists(const unsigned short projectId) const {
	return m_projects.at(projectId)->getLists();
}

QStringList Model::getTaskInfo(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) const {
    return m_projects.at(projectId)->getTaskInfo(listId,taskId);
}

std::string Model::getTaskName(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) const {
    return m_projects.at(projectId)->getTaskName(listId,taskId);
}

std::vector<std::pair<unsigned short, TaskType> > Model::getTasksIds(const unsigned short projectId, const unsigned short listId) const {
	return m_projects.at(projectId)->getTasksIds(listId);
}

QDateTime Model::getTaskPriority(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) const {
    return m_projects.at(projectId)->getTaskPriority(listId,taskId);
}

void Model::aggiornaTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId, const QStringList info) {
    m_projects.at(projectId)->aggiornaTask(listId,taskId,info);
}

void Model::deleteTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) {
    m_projects.at(projectId)->deleteTask(listId,taskId);
}

void Model::convertToPriority(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) {
    m_projects.at(projectId)->convertToPriority(listId,taskId);
}

void Model::convertToContainer(const unsigned short projectId, const unsigned short listId, const unsigned short taskId) {
    m_projects.at(projectId)->convertToContainer(listId,taskId);
}

void Model::dragAndDrop(const unsigned short projectId, const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short taskId, const unsigned short Posizione) {
    m_projects.at(projectId)->dragAndDrop(LPartenza,LArrivo,taskId,Posizione);
}

unsigned short Model::moveTask(const unsigned short projectId, const unsigned short listId, const unsigned short taskId, const Direction &moveDirection) {
     return m_projects.at(projectId)->moveTask(listId,taskId,moveDirection);
 }

void Model::load(const QJsonDocument& document) {
	if (document.isObject()) {
		Project* tmp = new Project(document.object());
		m_projects.insert(std::pair<unsigned short,Project*>(tmp->getId(), tmp));
		setActiveProject(tmp);
	}
}

QByteArray Model::save(const unsigned short projectId) {
	return QJsonDocument((projectId?m_projects.at(projectId):m_activeProject)->object()).toJson();
}

std::pair<unsigned short, std::string> Model::getProjectInfo(const unsigned short projectId) {

	Project* project = (projectId ? m_projects.at(projectId) : m_activeProject);

	return std::pair<unsigned short, std::string>(project->getId(), project->getName());
}
