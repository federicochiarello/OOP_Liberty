#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <typeinfo>

#include <QJsonDocument>
#include <QJsonArray>

#include "abstask.h"
#include "absproject.h"

template <class T>
class Project : public AbsProject {
private:
    const std::type_info&						m_priorityType;

public:
                                                Project(const Project& p_pro);
                                                Project(const std::string p_name =std::string());
                                                Project(QJsonDocument& p_doc);
	QJsonDocument	toJson() const;
};

#endif // PROJECT_H
