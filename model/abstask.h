#ifndef ABSTASK_H
#define ABSTASK_H

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

    static unsigned short int           nextID;
	static QString						dateTimeFormat;

	QDateTime	initEta(const QJsonValue& eta);
public:
//	Constructors and destructors
										explicit AbsTask(const std::string p_label =std::string(), const std::string p_desc =std::string(), List* p_list =nullptr, AbsTask* p_parent =nullptr);
										AbsTask(const QJsonObject& p_obj, AbsTask* p_parent =nullptr);
                                        AbsTask(const AbsTask& p_task);

    virtual								~AbsTask() =0;

//	Virtual methods
    virtual AbsTask*                    clone() const =0;
    //virtual QJsonObject&				toJson() const =0;
	virtual void						setList(List* p_list);
    virtual void                        aggiornaTask(const QStringList info);

//	Get methods
	std::string							getLabel() const;
	std::string							getDesc() const;
    QDateTime							getEta() const;
	AbsTask*							getParent() const;
	List*                               getList() const;
    unsigned short int                  getId() const;

//	Set methods
	void							  	setLabel(const std::string&);
	void								setDesc(const std::string&);
	void								setParent(AbsTask*);

};

#endif // ABSTASK_H
