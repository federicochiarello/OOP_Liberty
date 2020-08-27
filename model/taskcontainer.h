#ifndef TASKCONTAINER_H
#define TASKCONTAINER_H

#include <vector>
#include <QJsonArray>
#include "abstask.h"

class TaskContainer : virtual public AbsTask {
private:
    std::vector<AbsTask*>				m_child;

public:
										explicit TaskContainer(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr);
										explicit TaskContainer(const QJsonObject& object);
                                        TaskContainer(const TaskContainer& p_task);


    TaskContainer*                      clone() const override;
	void                                setList(List* p_list) override;
    //void                                aggiornaTask(const QStringList info) override;

    std::vector<AbsTask*>				getChilds() const;
    void								addChild(AbsTask*);
    void                                removeChild(AbsTask*);
    void                                addChildList(std::vector<AbsTask*> p_child);
    void                                updateChild(AbsTask* tOld, AbsTask* tNew);
};

#endif // TASKCONTAINER_H
