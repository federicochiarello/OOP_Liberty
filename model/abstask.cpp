#include "abstask.h"

unsigned short AbsTask::nextID = 0;
QString AbsTask::dateTimeFormat = "dd.MM.yyyy hh:mm:ss";

AbsTask::AbsTask(List* list, AbsTask* parent) :
	_id(++nextID),
	m_label(),
	m_desc(),
	m_eta(QDateTime::currentDateTime()),
	m_parent(parent),
	m_list(list) {}

AbsTask::AbsTask(const std::string p_label, const std::string p_desc, List* p_list, AbsTask* p_parent) :
	_id(++nextID),
    m_label(p_label),
    m_desc(p_desc),
    m_eta(QDateTime::currentDateTime()),
    m_parent(p_parent),
    m_list(p_list) {}

// Costruttore che consente di creare un oggetto con il campo _id desiderato
// la responsabilità di garantire l'unicità dell'id viene delegata alla funzione che compie la chiamata
AbsTask::AbsTask(const unsigned short id, const std::string p_label, const std::string p_desc) :
    _id(id),
    m_label(p_label),
    m_desc(p_desc),
    m_eta(QDateTime::currentDateTime()),
    m_parent(),
    m_list() {}

AbsTask::AbsTask(const QJsonObject& object, std::map<unsigned short,unsigned short>& idsMap) :
	_id(++nextID),
	m_label(object.value("taskLabel").toString().toStdString()),
	m_desc(object.value("taskDescription").toString().toStdString()),
	m_eta(QDateTime::fromString(object.value("taskEta").toString(), dateTimeFormat)),
	m_parent(nullptr),
	m_list() {
    idsMap.insert(std::pair<unsigned short,unsigned short>(object.value("taskId").toInt(), _id));
}

// Costruttore di copia: _id ha un valore differente dall' _id di p_task per garantire la coesistenza
// di una copia di p_task mantenendo l'unicità degli _id
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
	taskObject.insert("taskLabel", QJsonValue(QString::fromStdString(m_label)));
	taskObject.insert("taskDescription", QString::fromStdString(m_desc));
	taskObject.insert("taskEta", m_eta.toString(dateTimeFormat));
	taskObject.insert("taskParentId", (m_parent?m_parent->getId():0));

	return taskObject;
}

AbsTask::~AbsTask() {}

unsigned short  AbsTask::getId() const { return _id; }

std::string		AbsTask::getLabel() const { return m_label; }

std::string		AbsTask::getDesc() const { return m_desc; }

QDateTime		AbsTask::getEta() const { return m_eta; }

AbsTask*		AbsTask::getParent() const { return m_parent; }

List*           AbsTask::getList() const { return m_list; }

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
