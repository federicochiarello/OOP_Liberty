#include "model.h"

//  m_projects(new std::vector<Project*>())
Model::Model(const std::string path) : m_basePath(path), m_activeProject(nullptr) {}

Model::~Model() {
    if(! m_projects.empty())
        for(std::vector<Project*>::iterator i=m_projects.begin(); i!=m_projects.end(); i++)
            delete *i;
    //m_projects.clear();
}

void Model::createNewProject() {
    Project* p = new Project;
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

void Model::addNewList() {
    m_activeProject->addNewList();
}

void Model::addNewTask(const unsigned short int idList) {
    m_activeProject->addNewTask(idList, new Task());
}

void Model::setActiveProjName(const std::string& p_name) {
    m_activeProject->setName(p_name);
}

void Model::setListName(const unsigned short int idList, const std::string& p_name) {
    m_activeProject->setListName(idList,p_name);
}

void Model::ConvertToPriority(const unsigned short int idList, const unsigned short int idTask) {
    m_activeProject->ConvertToPriority(idList,idTask);
}
