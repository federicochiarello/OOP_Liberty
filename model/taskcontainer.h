#ifndef TASKCONTAINER_H
#define TASKCONTAINER_H

#include "abstask.h"

#include <vector>
#include <QJsonArray>
#include <QVariant>

class TaskContainer : virtual public AbsTask {
protected:
	std::vector<AbsTask*>				m_child;

public:
										explicit TaskContainer(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr);
                                        explicit TaskContainer(const QJsonObject& object, std::map<unsigned short,unsigned short>& idsMap);
                                        TaskContainer(const TaskContainer& p_task);

    TaskContainer*                      clone() const override;
    QJsonObject                         toJson() const override;
	void                                setList(List* p_list) override;
    QStringList                         getTaskInfo() const override;
    AbsTask*                            convertToContainer() const override;
    AbsTask*                            convertToPriority() const override;
	TaskType getType() const override;

    std::vector<AbsTask*>				getChilds() const;
    void								addChild(AbsTask*);
    void                                removeChild(AbsTask*);
    void                                addChildList(std::vector<AbsTask*> p_child);
    void                                updateChild(AbsTask* tOld, AbsTask* tNew);
};

#endif // TASKCONTAINER_H
