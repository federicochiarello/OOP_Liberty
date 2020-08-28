#ifndef ABSTASK_H
#define ABSTASK_H

#include <iostream>
#include <map>
#include <string>

#include <QJsonObject>
#include <QDateTime>

//	Dichiarazione Incompleta
class List;

class AbsTask {

	unsigned short						_id;
    std::string							m_label;
    std::string							m_desc;
    QDateTime							m_eta;
    AbsTask*							m_parent;
	List*                               m_list;

    static unsigned short               nextID;

	QDateTime	initEta(const QJsonValue& eta);

protected:
	static QString						dateTimeFormat;

public:
//	Constructors and destructors
										explicit AbsTask(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr);
										AbsTask(const QJsonObject& p_obj, std::map<unsigned short, unsigned short>& idsMap);
                                        AbsTask(const AbsTask& p_task);

    virtual								~AbsTask() =0;

//	Virtual methods
    virtual AbsTask*                    clone() const =0;
	virtual QJsonObject					toJson() const;
	virtual void						setList(List* p_list);
    virtual void                        aggiornaTask(const QStringList info);

//	Get methods
	std::string							getLabel() const;
	std::string							getDesc() const;
    QDateTime							getEta() const;
	AbsTask*							getParent() const;
	List*                               getList() const;
    unsigned short                      getId() const;

//	Set methods
	void							  	setLabel(const std::string&);
	void								setDesc(const std::string&);
	void								setParent(AbsTask*);

};

#endif // ABSTASK_H
