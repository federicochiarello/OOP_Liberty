#ifndef ABSTASK_H
#define ABSTASK_H

#include <string>
#include <ctime>
#include <QJsonObject>

class AbsTask {
private:
    std::string							m_label;
    std::string							m_desc;
	std::time_t							m_eta;
    AbsTask*							m_parent;
	std::string*						m_list;
public:
/* Constructors and destructors */
                                        AbsTask(const std::string p_label =std::string(), const std::string p_desc =std::string(), std::string* p_list =nullptr, AbsTask* p_parent =nullptr);
										AbsTask(const QJsonObject& p_obj, AbsTask* p_parent =nullptr);
                                        //AbsTask(const AbsTask& p_task, AbsTask* p_parent =nullptr);

    virtual								~AbsTask();

/* Virtual methods */
    virtual AbsTask*                    clone() const =0;
    virtual QJsonObject&				toJson() const =0;
    virtual void						setList(std::string* p_list);

/* Get methods */
	std::string							getLabel() const;
	std::string							getDesc() const;
	std::time_t							getEta() const;
	AbsTask*							getParent() const;
	std::string*						getList() const;
/* Set methods */
	void							  	setLabel(const std::string&);
	void								setDesc(const std::string&);
	void								setParent(AbsTask*);

};

#endif // ABSTASK_H
