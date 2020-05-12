#ifndef ABSELEMENT_H
#define ABSELEMENT_H

#include <string>
//ciaooo
class AbstractElement {
private:
	std::string							m_label;
//	std::string							m_content;
//	QDate								m_eta;
	AbstractElement*					m_parent;
public:
// Constructors and destructors
										AbstractElement(AbstractElement* =nullptr);
										AbstractElement(const std::string, AbstractElement* =nullptr);
										AbstractElement(const AbstractElement&, AbstractElement* =nullptr);

	virtual								~AbstractElement();

// Virtual methods
	virtual void						modifyLabel(std::string);
	virtual void						modifyContent() =0;

// Get methods

// Set methods



};

#endif // ABSELEMENT_H
