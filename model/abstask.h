#ifndef ABSTASK_H
#define ABSTASK_H

#include <string>
#include <ctime>

#include <QJsonObject>

class AbsTask {
private:
	AbsTask*							m_parent;
	std::time_t							m_eta;
	std::string*						m_list;
	std::string							m_label;
	std::string							m_desc;
public:
/* Constructors and destructors */
										AbsTask(std::string* p_list =nullptr, const std::string p_label =std::string(), const std::string p_desc =std::string(), AbsTask* p_parent =nullptr);
										AbsTask(const AbsTask& p_task, AbsTask* p_parent =nullptr);
										AbsTask(const QJsonObject& p_obj, AbsTask* p_parent =nullptr);

	virtual								~AbsTask();

/* Virtual methods */
	virtual QJsonObject&				toJson() const =0;
	virtual void						setList(std::string*);


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
/* Other methods */

};

#endif // ABSTASK_H
