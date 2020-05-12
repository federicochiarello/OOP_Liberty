#ifndef ABSTASK_H
#define ABSTASK_H

#include <string>
//ciaooo
class AbsTask {
private:
	std::string							m_label;
//	std::string							m_content;
//	QDate								m_eta;
	AbsTask*					m_parent;
public:
// Constructors and destructors
										AbsTask(AbsTask* =nullptr);
										AbsTask(const std::string, AbsTask* =nullptr);
										AbsTask(const AbsTask&, AbsTask* =nullptr);

	virtual								~AbsTask();

// Virtual methods
	virtual void						modifyLabel(std::string);
	virtual void						modifyContent() =0;

// Get methods

// Set methods



};

#endif // ABSTASK_H
