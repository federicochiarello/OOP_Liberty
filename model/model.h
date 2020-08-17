#ifndef MODEL_H
#define MODEL_H

#include "absproject.h"

class Model {
private:
	std::string						m_basePath;
    std::vector<AbsProject*>		m_projects;
	AbsProject*						m_activeProject;
public:
	Model();
};

#endif // MODEL_H
