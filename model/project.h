#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <map>
#include <vector>

#include <QJsonDocument>

#include "../veqtor.h"
#include "abstask.h"

class Project {
private:
	std::string														m_name;
	std::map<std::string, std::vector<AbsTask*>>					m_lists;
	std::vector<std::string*>										m_listOrder;

public:
																	Project(const Project& p_pro);
																	Project(const std::string p_name =std::string());
																	Project(QJsonDocument& p_doc);

	void															removeFromList(AbsTask*);
};

#endif // PROJECT_H
