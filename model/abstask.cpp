#include "abstask.h"

AbsTask::AbsTask(const std::string p_label, const std::string p_desc, std::string* p_list, AbsTask* p_parent) :
    m_label(p_label),
    m_desc(p_desc),
	m_eta(time(nullptr)),
    m_parent(p_parent),
    m_list(p_list) {}

AbsTask::AbsTask(const AbsTask& p_task, AbsTask* p_parent) :
    m_label(p_task.m_label),
    m_desc(p_task.m_desc),
    m_eta(time(nullptr)),
    m_parent(p_parent),
    m_list(p_task.m_list) {}

AbsTask::AbsTask(const QJsonObject& p_obj, AbsTask* p_parent) :
    m_label(p_obj.value("label").toString().toStdString()),
    m_desc(p_obj.value("desc").toString().toStdString()),
	m_eta(p_obj.value("eta").toInt()),
    m_parent(p_parent),
    m_list() {}

std::string		AbsTask::getLabel() const { return m_label; }

std::string		AbsTask::getDesc() const { return m_desc; }

std::time_t		AbsTask::getEta() const { return m_eta; }

AbsTask*		AbsTask::getParent() const { return m_parent; }

std::string*	AbsTask::getList() const { return m_list; }

void			AbsTask::setLabel(const std::string& p_label) { m_label = p_label; }

void			AbsTask::setDesc(const std::string& p_desc) { m_desc = p_desc; }

void			AbsTask::setParent(AbsTask* p_parent) { m_parent = p_parent; }

void			AbsTask::setList(std::string* p_list) { m_list = p_list; }
