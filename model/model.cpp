#include "model.h"

//  m_projects(new std::vector<Project*>())
Model::Model(const std::string path) : m_basePath(path), m_activeProject(nullptr) {}

Model::~Model() {
    if(! m_projects.empty())
        for(std::vector<Project*>::iterator i=m_projects.begin(); i!=m_projects.end(); i++)
            delete *i;
    //m_projects.clear();
}

void Model::createNewProject(const std::string& p_name) {
    Project* p = new Project(p_name);
    m_projects.push_back(p);
    m_activeProject = p;
}

void Model::setActiveProject(const unsigned int indP) {
    m_activeProject = m_projects[indP];
}

void Model::deleteProject(const unsigned int indP) {
    Project* p = m_projects[indP];
    if(m_activeProject == p)
        m_activeProject = nullptr;

    m_projects.erase(m_projects.begin() + indP);
    delete p;
}
/*
void Model::addNewList() {
    m_activeProject->addNewList();
}
*/
unsigned short Model::addNewList() {
    return m_activeProject->addNewList();
}

unsigned short Model::addNewTask(const unsigned short idList) {
    return m_activeProject->addNewTask(idList);
}

unsigned short Model::addNewTaskChild(const unsigned short idList, const unsigned short idTask) {
    return m_activeProject->addNewTask(idList,idTask);
}

/*
void Model::addNewTask(const unsigned short int idList) {
    m_activeProject->addNewTask(idList, new Task());
}
*/
void Model::setActiveProjName(const std::string& p_name) {
    m_activeProject->setName(p_name);
}

void Model::setListName(const unsigned short idList, const std::string& p_name) {
    m_activeProject->setListName(idList,p_name);
}

void Model::changeListOrder(const unsigned short listToMove, const unsigned short Posizione) {
    m_activeProject->changeListOrder(listToMove,Posizione);
}

QStringList Model::getTaskInfo(const unsigned short idList, const unsigned short idTask) const {
    return m_activeProject->getTaskInfo(idList,idTask);
}

void Model::aggiornaTask(const unsigned short idList, const unsigned short idTask, const QStringList info) {
    m_activeProject->aggiornaTask(idList,idTask,info);
}

unsigned short int Model::convertToPriority(const unsigned short idList, const unsigned short idTask) {
    return m_activeProject->convertToPriority(idList,idTask);
}

unsigned short int Model::convertToContainer(const unsigned short idList, const unsigned short idTask) {
    return m_activeProject->convertToContainer(idList,idTask);
}

void Model::dragAndDrop(const unsigned short LPartenza, const unsigned short LArrivo, const unsigned short idTask, const unsigned short Posizione) {
    m_activeProject->dragAndDrop(LPartenza,LArrivo,idTask,Posizione);
}
