#include "projectview.h"

//ProjectView::ProjectView(QWidget *parent) :
//	QWidget(parent),
//	_mainLayout(new QVBoxLayout()),
//	_centralLayout(new QHBoxLayout()) {
//	setup();
//	//addList("Prova");
//}

ProjectView::ProjectView(const std::pair<unsigned short, QString>& projectInfo, const Controller* controller, QWidget *parent) :
	QWidget(parent),
	_id(projectInfo.first),
	_lists(),
	_controller(controller),
	_mainLayout(new QVBoxLayout()),
	_centralLayout(new QHBoxLayout()),
	_projectName(new QLineEdit(projectInfo.second, this)),
	_buttonAddList(new QPushButton(tr("+"), this)){

	connects();
	setup();
	qDebug() << "Project created";

	emit getLists(_id);
}

unsigned short ProjectView::getId() const { return _id; }

void ProjectView::connects() {
	connect(this, SIGNAL(getLists(const unsigned short)),
			_controller, SLOT(onGetLists(const unsigned short)));

	connect(_controller, SIGNAL(sendListsIds(const unsigned short, std::vector<unsigned short>)),
			this, SLOT(fetchListsIds(const unsigned short, std::vector<unsigned short>)));
}

void ProjectView::setup() {
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	setLayout(_mainLayout);

	_mainLayout->addWidget(_projectName);
	_centralLayout->addWidget(_buttonAddList);
	_mainLayout->addLayout(_centralLayout);
}

//ProjectView::ProjectView(const unsigned short id, const Controller *controller, QWidget *parent) :
//	_id(id),
//	_lists(),
//	_controller(controller) {

//}

void ProjectView::newList() {
	//TasksList* newTaskList = new TasksList(this);
//	_lists.push_back(new TasksListWidget(this));
	//QLineEdit* listName = new QLineEdit(tr(""), this);
	//connect(_lists.back(), SIGNAL(newList()), this, SLOT(addList()));
//	_centralLayout->insertWidget(_centralLayout->count()-1, _lists.back());
}


void ProjectView::addList(std::string listName) {
	_mainLayout->addWidget(dynamic_cast<TasksListWidget*>(_lists.back()));
}

void ProjectView::fetchListsIds(const unsigned short projectId, std::vector<unsigned short> listsIds) {
	if (_id == projectId) {
		_centralLayout->removeWidget(_buttonAddList);
		qDebug() << "fetchLists";
		for (auto listId : listsIds) {
			TasksListWidget* list = new TasksListWidget(listId, _id, _controller, this);
			_lists.push_back(list);
			_centralLayout->addWidget(list);
//			connect(list, SIGNAL(getListName(const unsigned short)),
//					this, SIGNAL(getListName(const unsigned short)));

//			connect(this, SIGNAL(sendListName(const unsigned short, const QString&)),
//					list, SLOT(fetchListName(const unsigned short, const QString&)));

//			connect(this, SIGNAL(sendTasksIds(const unsigned short, const std::vector<std::pair<unsigned short, TaskType>>)),
//					list, SLOT(fetchTasksIds(const unsigned short, const std::vector<std::pair<unsigned short, TaskType>>))); eliminato


//			emit list->getListName(list->getId());
		}
	}
	_centralLayout->addWidget(_buttonAddList);
}

//void ProjectView::onGetListName(const unsigned short listId) {
//	emit getListName(_id, listId);
//}

//void ProjectView::fetchListName(const unsigned short projectId, const unsigned short listId, const QString& listName) {
//	if (projectId == _id) {
//		emit sendListName(listId, listName);
//	}
//}

//void ProjectView::onGetTasksIds(const unsigned short listId) {
//	emit getTasksIds(_id, listId);
//}
