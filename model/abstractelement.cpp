#include "abstractelement.h"

AbstractElement::AbstractElement(AbstractElement* p_parent) : m_parent(p_parent) {}

AbstractElement::AbstractElement(const std::string p_label, AbstractElement* p_parent) : m_label(p_label), m_parent(p_parent) {}

AbstractElement::AbstractElement(const AbstractElement& p_el, AbstractElement* p_parent) : m_label(p_el.m_label), m_parent(p_parent) {}
