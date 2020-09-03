#ifndef TASKCONTAINER_H
#define TASKCONTAINER_H

#include <QJsonArray>
#include <QVariant>
#include "veqtor.h"

#include "abstask.h"

class TaskContainer : virtual public AbsTask {
private:
    veqtor<AbsTask*>        m_child;

public:
                            explicit TaskContainer(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr);
                            explicit TaskContainer(const QJsonObject& object, std::map<unsigned short,unsigned short>& idsMap, std::map<unsigned short, veqtor<unsigned short>>& childsMap);
                            explicit TaskContainer(const unsigned short id, const std::string p_label, const std::string p_desc);
                            TaskContainer(const TaskContainer& p_task);
                            ~TaskContainer() override;

    TaskContainer*          clone() const override;
    QJsonObject             toJson() const override;
    void                    setList(List* p_list) override;
    QStringList             getTaskInfo() const override;
    AbsTask*                convertToContainer() const override;
    AbsTask*                convertToPriority() const override;
    TaskType                getType() const override;

    veqtor<AbsTask*>		getChilds() const;
    void					addChild(AbsTask*);
    void                    removeChild(AbsTask*);
    void                    addChildList(veqtor<AbsTask*> p_child);
    void                    updateChild(AbsTask* tOld, AbsTask* tNew);
};

#endif // TASKCONTAINER_H
