#ifndef ABSTASK_H
#define ABSTASK_H

#include <string>

#include <QJsonObject>

#include "datetime.h"

class AbsTask {
private:
	std::string							m_label;
	std::string							m_desc;
	DateTime							m_eta;
	AbsTask*							m_parent;
public:
/* Constructors and destructors */
										AbsTask(AbsTask* p_parent =nullptr);
										AbsTask(const std::string p_label, AbsTask* p_parent =nullptr);
										AbsTask(const std::string p_label, const std::string p_desc, AbsTask* p_parent =nullptr);
										AbsTask(const AbsTask& p_task, AbsTask* p_parent =nullptr);
										AbsTask(const QJsonObject& p_obj, AbsTask* p_parent =nullptr);

	virtual								~AbsTask();

/* Virtual methods */
	virtual QJsonObject&				toJson() const =0;


/* Get methods */
	const std::string					getLabel() const;
	const std::string					getDesc() const;
	const DateTime						getEta() const;
	const AbsTask*						getParent() const;
/* Set methods */
	void								setLabel(const std::string);
	void								setDesc(const std::string);
	void								setParent(const AbsTask*);
/* Other methods */

};

#endif // ABSTASK_H
