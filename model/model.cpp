#include "model.h"

//  m_projects(new std::vector<Project*>())
Model::Model(const std::string path) : m_basePath(path), m_activeProject(nullptr) {}

Model::~Model() {
    m_projects.clear();
}

void Model::setActiveProject(const unsigned int indP) {
    m_activeProject = m_projects[indP];
}

void Model::deleteProject(const unsigned int indP) {
    if(m_activeProject == m_projects[indP])
        m_activeProject = nullptr;
    m_projects.erase(m_projects.begin() + indP);
}

void Model::addNewList() {
    m_activeProject->addNewList();
}

void Model::addNewTask(const unsigned int indL) {
    m_activeProject->addNewTask(indL, new Task());
}

void Model::setActiveProjName(const std::string& p_name) {
    m_activeProject->setName(p_name);
}

void Model::setListName(const unsigned int indL, const std::string& p_name) {
    m_activeProject->setListName(indL,p_name);
}

void Model::ConvertToPriority(const unsigned int indL, const unsigned int indT) {
    //m_activeProject->ConvertToPriority(indL,indT);
}
