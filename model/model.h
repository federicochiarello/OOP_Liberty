#ifndef MODEL_H
#define MODEL_H

#include "veqtor.h"
#include "project.h"

class Model {
private:
	std::string						m_basePath;
	std::vector<std::string>		m_projects;
	AbsProject*						m_activeProject;
public:
	Model();
};

#endif // MODEL_H
