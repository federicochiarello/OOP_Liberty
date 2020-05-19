#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <map>
#include <vector>
#include <typeinfo>

#include <QJsonDocument>
#include <QJsonArray>

#include "veqtor.h"
#include "abstask.h"

class AbsProject {
/*
 * Portare qua tutti i metodi e gli attributi che non hanno a che fare con il template e mettere il resto in Project
*/
public:
	AbsProject();
};

template <class T>
class Project : public AbsProject {
private:
	std::string														m_name;
	std::vector<AbsTask*>											m_tasks;
	std::map<std::string, std::vector<AbsTask*>>					m_lists;
	std::vector<std::string*>										m_listOrder;
	const std::type_info&											m_priorityType;

public:
																	Project(const Project& p_pro);
																	Project(const std::string p_name =std::string());
																	Project(QJsonDocument& p_doc);

	QJsonDocument	toJson() const;
	void	removeFromList(AbsTask*);
	void	addToList(AbsTask*);
};

#endif // PROJECT_H
