#include "abstask.h"


unsigned short AbsTask::nextID = 0;
QString AbsTask::dateTimeFormat = "dd/MM/yyyy hh:mm:ss";

AbsTask::AbsTask(const std::string p_label, const std::string p_desc, List* p_list, AbsTask* p_parent) :
	_id(++nextID),
    m_label(p_label),
    m_desc(p_desc),
    m_eta(QDateTime::currentDateTime()),
    m_parent(p_parent),
	m_list(p_list) {}

AbsTask::AbsTask(const QJsonObject& object, std::map<const unsigned short, const unsigned short>& idsMap) :
	_id(++nextID),
	m_label(object.value("taskLabel").toString().toStdString()),
	m_desc(object.value("taskDescription").toString().toStdString()),
	m_eta(QDateTime::fromString(object.value("taskEta").toString(), dateTimeFormat)),
	m_parent(nullptr),
	m_list() {
	idsMap.insert(std::pair<const unsigned short, const unsigned short>(object.value("taskId").toInt(), _id));
}

AbsTask::AbsTask(const AbsTask &p_task) :
	_id(++nextID),
    m_label(p_task.m_label),
    m_desc(p_task.m_desc),
    m_eta(QDateTime::currentDateTime()),
	m_parent(p_task.m_parent),
	m_list(p_task.m_list) {}

QJsonObject AbsTask::toJson() const {

	QJsonObject taskObject;

	taskObject.insert("taskId", _id);
	taskObject.insert("taskLabel", QString::fromStdString(m_label));
	taskObject.insert("taskDescription", QString::fromStdString(m_desc));
	taskObject.insert("taskEta", m_eta.toString(dateTimeFormat));
	taskObject.insert("taskParentID", m_parent->getId());

	return taskObject;
}


AbsTask::~AbsTask() {}

std::string		AbsTask::getLabel() const { return m_label; }

std::string		AbsTask::getDesc() const { return m_desc; }

QDateTime		AbsTask::getEta() const { return m_eta; }

AbsTask*		AbsTask::getParent() const { return m_parent; }

List*           AbsTask::getList() const { return m_list; }

const unsigned short  AbsTask::getId() const { return _id; }

void			AbsTask::setLabel(const std::string& p_label) { m_label = p_label; }

void			AbsTask::setDesc(const std::string& p_desc) { m_desc = p_desc; }

void			AbsTask::setParent(AbsTask* p_parent) { m_parent = p_parent; }

void			AbsTask::setList(List* p_list) { m_list = p_list; }

void AbsTask::aggiornaTask(const QStringList info) {
    setLabel(info[0].toStdString());
    setDesc(info[1].toStdString());
}

QStringList AbsTask::getTaskInfo() const {
    QStringList tmp;
    tmp.push_back(QString::fromStdString(getLabel()));
    tmp.push_back(QString::fromStdString(getDesc()));
    return tmp;
}
