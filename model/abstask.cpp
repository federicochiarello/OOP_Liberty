#include "abstask.h"
#include <iostream>
unsigned short int AbsTask::nextID = 0;

AbsTask::AbsTask(const std::string p_label, const std::string p_desc, List* p_list, AbsTask* p_parent) :
    m_label(p_label),
    m_desc(p_desc),
    m_eta(QDateTime::currentDateTime()),
    m_parent(p_parent),
	m_list(p_list),
    id(++nextID)    {}

AbsTask::AbsTask(const AbsTask &p_task) :
    m_label(p_task.m_label),
    m_desc(p_task.m_desc),
    m_eta(QDateTime::currentDateTime()),
    m_parent(p_task.m_parent),
	m_list(p_task.m_list),
    id(++nextID)    {}
/*
AbsTask::AbsTask(const QJsonObject& p_obj, AbsTask* p_parent) :
	m_label(p_obj.value("label").toString().toStdString()),
	m_desc(p_obj.value("desc").toString().toStdString()),
    //m_eta(p_obj.value("eta").toInt()),
	m_parent(p_parent),
	m_list(),
    id(++nextID)    {}
*/
AbsTask::~AbsTask() {}

std::string		AbsTask::getLabel() const { return m_label; }

std::string		AbsTask::getDesc() const { return m_desc; }

QDateTime		AbsTask::getEta() const { return m_eta; }

AbsTask*		AbsTask::getParent() const { return m_parent; }

List*           AbsTask::getList() const { return m_list; }

unsigned short  AbsTask::getId() const { return id; }

void			AbsTask::setLabel(const std::string& p_label) { m_label = p_label; }

void			AbsTask::setDesc(const std::string& p_desc) { m_desc = p_desc; }

void			AbsTask::setParent(AbsTask* p_parent) { m_parent = p_parent; }

void			AbsTask::setList(List* p_list) { m_list = p_list; }

void AbsTask::aggiornaTask(const QStringList info) {
    setLabel(info[0].toStdString());
    setDesc(info[1].toStdString());
}
