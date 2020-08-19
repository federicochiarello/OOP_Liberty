#ifndef ABSPROJECT_H
#define ABSPROJECT_H

#include <string>
#include <vector>

#include <QJsonDocument>
#include <QJsonArray>

#include "abstask.h"
#include "list.h"

class AbsProject {
private:
    std::string                             m_name;
    std::vector<List*>                      m_lists;

    // Old
    // std::vector<AbsTask*>								m_tasks;
    // std::map<std::string, std::vector<AbsTask*>>			m_lists;

public:
                                            AbsProject(std::string p_name = std::string());

    void                                    addList(List* p_list);
    void                                    removeList(List* p_list);

    void                                    setName(const std::string p_name);
    std::string                             getName() const;
    std::vector<List*>                      getLists() const;
};

#endif // ABSPROJECT_H
