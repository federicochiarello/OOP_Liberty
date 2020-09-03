#ifndef ABSTASK_H
#define ABSTASK_H

#include <string>
#include <map>
#include <QDateTime>
#include <QJsonObject>

#include "src/globalenums.h"

#include <QDebug>

class List;

class AbsTask {
private:

    const unsigned short				_id;
    std::string							m_label;
    std::string							m_desc;
    QDateTime							m_eta;
    AbsTask*							m_parent;
	List*                               m_list;

    static unsigned short               nextID;

    QDateTime                           initEta(const QJsonValue& eta);

protected:

	static QString						dateTimeFormat;

public:
										explicit AbsTask(List* p_list =nullptr, AbsTask* p_parent =nullptr);
										explicit AbsTask(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr);
                                        explicit AbsTask(const unsigned short id, const std::string p_label =std::string(), const std::string p_desc =std::string());
                                        AbsTask(const QJsonObject& p_obj, std::map<unsigned short,unsigned short>& idsMap);
                                        AbsTask(const AbsTask& p_task);
    virtual								~AbsTask() =0;

//	VIRTUAL METHODS
    virtual AbsTask*                    clone() const =0;
	virtual QJsonObject					toJson() const;
	virtual void						setList(List* p_list);
    virtual void                        aggiornaTask(const QStringList info);
    virtual QStringList                 getTaskInfo() const;
    virtual AbsTask*                    convertToContainer() const =0;
    virtual AbsTask*                    convertToPriority() const =0;
	virtual TaskType					getType() const =0;

//	virtual std::pair<TaskType, QStringList> getTaskInfo() const =0;

    unsigned short                      getId() const;
	std::string							getLabel() const;
	std::string							getDesc() const;
    QDateTime							getEta() const;
	AbsTask*							getParent() const;
	List*                               getList() const;

	void							  	setLabel(const std::string&);
	void								setDesc(const std::string&);
	void								setParent(AbsTask*);
};

#endif // ABSTASK_H
