#include "projectview.h"

//ProjectView::ProjectView(QWidget *parent) :
//	QWidget(parent),
//	_mainLayout(new QVBoxLayout()),
//	_centralLayout(new QHBoxLayout()) {
//	setup();
//	//addList("Prova");
//}

ProjectView::ProjectView(const std::pair<const unsigned short, const QString&>& projectInfo, const Controller* controller, QWidget *parent) :
	QWidget(parent),
	_id(projectInfo.first),
	_controller(controller) {

}

unsigned short ProjectView::getId() const { return _id; }

void ProjectView::connects() {
	connect(this, SIGNAL(getLists(const unsigned short)),
			_controller, SLOT(onGetLists(const unsigned short)));

	connect(_controller, SIGNAL(sendListsIds(const unsigned short, const std::vector<const unsigned short>)),
			this, SLOT(fetchListsIds(const unsigned short, const std::vector<const unsigned short>)));
}

void ProjectView::setup(std::string name) {
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	setLayout(_mainLayout);
	{
		QLineEdit* title = new QLineEdit(QString::fromStdString(name), this);
		_mainLayout->addWidget(title);
	}

	{
		QPushButton* new_ = new QPushButton(tr("+"), this);
		connect(new_, SIGNAL(clicked()), this, SLOT(newList()));
		_centralLayout->addWidget(new_);
	}
	_mainLayout->addLayout(_centralLayout);
}

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

void ProjectView::fetchListsIds(const unsigned short projectId, const std::vector<const unsigned short> listsIds) {
	if (_id == projectId) {
		for (auto listId : listsIds) {
			TasksListWidget* list = new TasksListWidget(listId, _id, _controller, this);
			_lists.push_back(list);

//			connect(list, SIGNAL(getListName(const unsigned short)),
//					this, SIGNAL(getListName(const unsigned short)));

//			connect(this, SIGNAL(sendListName(const unsigned short, const QString&)),
//					list, SLOT(fetchListName(const unsigned short, const QString&)));

//			connect(this, SIGNAL(sendTasksIds(const unsigned short, const std::vector<std::pair<unsigned short, TaskType>>)),
//					list, SLOT(fetchTasksIds(const unsigned short, const std::vector<std::pair<unsigned short, TaskType>>))); eliminato


//			emit list->getListName(list->getId());
		}
	}
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
